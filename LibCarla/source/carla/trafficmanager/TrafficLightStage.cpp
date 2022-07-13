
#include "carla/trafficmanager/Constants.h"
#include "carla/trafficmanager/LocalizationUtils.h"

#include "carla/trafficmanager/TrafficLightStage.h"

namespace carla {
namespace traffic_manager {

using constants::TrafficLight::EXIT_JUNCTION_THRESHOLD;
using constants::TrafficLight::MINIMUM_STOP_TIME;
using constants::WaypointSelection::JUNCTION_LOOK_AHEAD;
using constants::MotionPlan::EPSILON_RELATIVE_SPEED;

TrafficLightStage::TrafficLightStage(
  const std::vector<ActorId> &vehicle_id_list,
  const SimulationState &simulation_state,
  const BufferMap &buffer_map,
  const Parameters &parameters,
  const cc::World &world,
  TLFrame &output_array,
  RandomGenerator &random_device)
  : vehicle_id_list(vehicle_id_list),
    simulation_state(simulation_state),
    buffer_map(buffer_map),
    parameters(parameters),
    world(world),
    output_array(output_array),
    random_device(random_device) {}

void TrafficLightStage::Update(const unsigned long index) {
  bool traffic_light_hazard = false;

  const ActorId ego_actor_id = vehicle_id_list.at(index);
  if (!simulation_state.IsDormant(ego_actor_id)) {
    const Buffer &waypoint_buffer = buffer_map.at(ego_actor_id);
    const SimpleWaypointPtr look_ahead_point = GetTargetWaypoint(waypoint_buffer, JUNCTION_LOOK_AHEAD).first;

    const Junction junction = look_ahead_point->GetWaypoint()->GetJunction();
    current_timestamp = world.GetSnapshot().GetTimestamp();

    const TrafficLightState tl_state = simulation_state.GetTLS(ego_actor_id);
    const TLS traffic_light_state = tl_state.tl_state;
    const bool is_at_traffic_light = tl_state.at_traffic_light;

    // We determine to stop if the vehicle found a traffic light in yellow / red.
    if (is_at_traffic_light &&
        traffic_light_state != TLS::Green &&
        traffic_light_state != TLS::Off &&
        parameters.GetPercentageRunningLight(ego_actor_id) <= random_device.next()) {

      traffic_light_hazard = true;
    }
    // The vehicle is currently at a non signalized junction, so handle its priorities.
    // Don't use the next condition as bounding boxes might switch to green
    else if (vehicle_last_junction.find(ego_actor_id) != vehicle_last_junction.end())
    {
      if (!look_ahead_point->CheckJunction()) {
        // Very close to the junction exit, forget about it.
        RemoveActor(ego_actor_id);
      }
      else {
        auto junction_id = junction->GetId();
        if (exiting_vehicles_map.find(junction_id) != exiting_vehicles_map.end()) {
          auto& exiting_vehicles = exiting_vehicles_map.at(junction_id);
          if (std::find(exiting_vehicles.begin(), exiting_vehicles.end(), ego_actor_id) != exiting_vehicles.end()) {
            // The vehicle is exitting the junction.
            traffic_light_hazard =  false;
          }
          else {
            // Vehicle entering the junction, handle it
            traffic_light_hazard = HandleNonSignalisedJunction(ego_actor_id, junction, waypoint_buffer, current_timestamp);
          }
        }
      }
    }
    else if (look_ahead_point->CheckJunction() &&
            !is_at_traffic_light &&
            traffic_light_state != TLS::Green &&
            parameters.GetPercentageRunningSign(ego_actor_id) <= random_device.next()) {

      AddActorToNonSignalisedJunction(ego_actor_id, junction);
      traffic_light_hazard = true;
    }
  }
  output_array.at(index) = traffic_light_hazard;
}

void TrafficLightStage::AddActorToNonSignalisedJunction(const ActorId ego_actor_id, const Junction junction) {

  auto junction_id = junction->GetId();

  if (entering_vehicles_map.find(junction_id) == entering_vehicles_map.end()) {
    // Initializing new map entry for the junction with an empty actor deque.
    std::deque<ActorId> entry_deque;
    std::deque<ActorId> exit_deque;
    entering_vehicles_map.insert({junction_id, entry_deque});
    exiting_vehicles_map.insert({junction_id, exit_deque});
  }

  auto& entering_vehicles = entering_vehicles_map.at(junction_id);
  if (std::find(entering_vehicles.begin(), entering_vehicles.end(), ego_actor_id) == entering_vehicles.end()){
    // Initializing new actor entry to the junction maps.
    entering_vehicles.push_back(ego_actor_id);
    if (vehicle_last_junction.find(ego_actor_id) != vehicle_last_junction.end()) {
      // The actor was entering another junction, so remove all of its stored data
      RemoveActor(ego_actor_id);
    }
    vehicle_last_junction.insert({ego_actor_id, junction_id});
  }
}


bool TrafficLightStage::HandleNonSignalisedJunction(const ActorId ego_actor_id, const Junction junction,
                                                    const Buffer &waypoint_buffer, cc::Timestamp timestamp) {

  bool traffic_light_hazard = false;
  auto junction_id = junction->GetId();

  auto& entering_vehicles = entering_vehicles_map.at(junction_id);
  auto& exiting_vehicles = exiting_vehicles_map.at(junction_id);

  if (vehicle_stop_time.find(ego_actor_id) == vehicle_stop_time.end()) {
    // Ensure the vehicle stops before doing anything else
    if (simulation_state.GetVelocity(ego_actor_id).Length() < EPSILON_RELATIVE_SPEED) {
      vehicle_stop_time.insert({ego_actor_id, timestamp});
    }
    traffic_light_hazard = true;
  }

  else if (entering_vehicles.front() == ego_actor_id) {
    auto entry_elapsed_seconds = vehicle_stop_time.at(ego_actor_id).elapsed_seconds;
    if (timestamp.elapsed_seconds - entry_elapsed_seconds < MINIMUM_STOP_TIME) {
      // Wait at least the minimum amount of time before entering the junction
      traffic_light_hazard = true;
    }
    else {
      auto ego_heading = simulation_state.GetHeading(ego_actor_id);
      for (auto &exiting_vehicle_id : exiting_vehicles) {
        auto exiting_heading = simulation_sate.GetHeading(exiting_vehicle_id);
        if (cg::Math::Dot(ego_heading, exiting_heading) > ENTERING_ANGLE_THRESHOLD) {
          traffic_light_hazard = true;
        }
      }

      // Track the first actor until it has passed the mid-point
      cg::Transform actor_transform = waypoint_buffer.front()->GetTransform();
      cg::Vector3D forward_vec = actor_transform.GetForwardVector();
      cg::Vector3D to_center_vec = junction->GetBoundingBox().location - actor_transform.location;

      if (cg::Math::Dot(forward_vec, to_center_vec) < EXIT_JUNCTION_THRESHOLD) {
        // Remove it from the entry data, letting the next one enter it
        entering_vehicles.pop_front();
        vehicle_stop_time.erase(ego_actor_id);
        exiting_vehicles_map.at(junction_id).push_back(ego_actor_id);
      }
    }

  } else {
    // Only one vehicle can be entering the junction, so stop the rest.
    traffic_light_hazard = true;
  }
  return traffic_light_hazard;
}

void TrafficLightStage::RemoveActor(const ActorId actor_id) {
  if (vehicle_last_junction.find(actor_id) != vehicle_last_junction.end()) {
    auto junction_id = vehicle_last_junction.at(actor_id);

    auto& entering_vehicles = entering_vehicles_map.at(junction_id);
    auto ent_index = std::find(entering_vehicles.begin(), entering_vehicles.end(), actor_id);
    if (ent_index != entering_vehicles.end()) {
      entering_vehicles.erase(ent_index);
    }

    auto& exiting_vehicles = exiting_vehicles_map.at(junction_id);
    auto ext_index = std::find(exiting_vehicles.begin(), exiting_vehicles.end(), actor_id);
    if (ext_index != exiting_vehicles.end()) {
      exiting_vehicles.erase(ext_index);
    }

    if (vehicle_stop_time.find(actor_id) != vehicle_stop_time.end()) {
      vehicle_stop_time.erase(actor_id);
    }

    vehicle_last_junction.erase(actor_id);
  }
}

void TrafficLightStage::Reset() {
  entering_vehicles_map.clear();
  exiting_vehicles_map.clear();
  vehicle_last_junction.clear();
  vehicle_stop_time.clear();
}

} // namespace traffic_manager
} // namespace carla
