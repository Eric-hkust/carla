// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file CarlaEgoCarlaEgoVehicleControl.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _FAST_DDS_GENERATED_CARLA_MSGS_MSG_CARLAEGOCarlaEgoVehicleControl_H_
#define _FAST_DDS_GENERATED_CARLA_MSGS_MSG_CARLAEGOCarlaEgoVehicleControl_H_

#include "Header.h"

#include <fastrtps/utils/fixed_size_string.hpp>

#include <stdint.h>
#include <array>
#include <string>
#include <vector>
#include <map>
#include <bitset>

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define eProsima_user_DllExport
#endif  // _WIN32

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(CarlaEgoCarlaEgoVehicleControl_SOURCE)
#define CarlaEgoCarlaEgoVehicleControl_DllAPI __declspec( dllexport )
#else
#define CarlaEgoCarlaEgoVehicleControl_DllAPI __declspec( dllimport )
#endif // CarlaEgoCarlaEgoVehicleControl_SOURCE
#else
#define CarlaEgoCarlaEgoVehicleControl_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define CarlaEgoCarlaEgoVehicleControl_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
} // namespace fastcdr
} // namespace eprosima


namespace carla_msgs {
    namespace msg {
        /*!
         * @brief This class represents the structure CarlaEgoVehicleControl defined by the user in the IDL file.
         * @ingroup CarlaEgoVehicleControl
         */
        class CarlaEgoVehicleControl
        {
        public:

            /*!
             * @brief Default constructor.
             */
            eProsima_user_DllExport CarlaEgoVehicleControl();

            /*!
             * @brief Default destructor.
             */
            eProsima_user_DllExport ~CarlaEgoVehicleControl();

            /*!
             * @brief Copy constructor.
             * @param x Reference to the object carla_msgs::msg::CarlaEgoVehicleControl that will be copied.
             */
            eProsima_user_DllExport CarlaEgoVehicleControl(
                    const CarlaEgoVehicleControl& x);

            /*!
             * @brief Move constructor.
             * @param x Reference to the object carla_msgs::msg::CarlaEgoVehicleControl that will be copied.
             */
            eProsima_user_DllExport CarlaEgoVehicleControl(
                    CarlaEgoVehicleControl&& x) noexcept;

            /*!
             * @brief Copy assignment.
             * @param x Reference to the object carla_msgs::msg::CarlaEgoVehicleControl that will be copied.
             */
            eProsima_user_DllExport CarlaEgoVehicleControl& operator =(
                    const CarlaEgoVehicleControl& x);

            /*!
             * @brief Move assignment.
             * @param x Reference to the object carla_msgs::msg::CarlaEgoVehicleControl that will be copied.
             */
            eProsima_user_DllExport CarlaEgoVehicleControl& operator =(
                    CarlaEgoVehicleControl&& x) noexcept;

            /*!
             * @brief Comparison operator.
             * @param x carla_msgs::msg::CarlaEgoVehicleControl object to compare.
             */
            eProsima_user_DllExport bool operator ==(
                    const CarlaEgoVehicleControl& x) const;

            /*!
             * @brief Comparison operator.
             * @param x carla_msgs::msg::CarlaEgoVehicleControl object to compare.
             */
            eProsima_user_DllExport bool operator !=(
                    const CarlaEgoVehicleControl& x) const;

            /*!
             * @brief This function copies the value in member header
             * @param _header New value to be copied in member header
             */
            eProsima_user_DllExport void header(
                    const std_msgs::msg::Header& _header);

            /*!
             * @brief This function moves the value in member header
             * @param _header New value to be moved in member header
             */
            eProsima_user_DllExport void header(
                    std_msgs::msg::Header&& _header);

            /*!
             * @brief This function returns a constant reference to member header
             * @return Constant reference to member header
             */
            eProsima_user_DllExport const std_msgs::msg::Header& header() const;

            /*!
             * @brief This function returns a reference to member header
             * @return Reference to member header
             */
            eProsima_user_DllExport std_msgs::msg::Header& header();
            /*!
             * @brief This function sets a value in member throttle
             * @param _throttle New value for member throttle
             */
            eProsima_user_DllExport void throttle(
                    float _throttle);

            /*!
             * @brief This function returns the value of member throttle
             * @return Value of member throttle
             */
            eProsima_user_DllExport float throttle() const;

            /*!
             * @brief This function returns a reference to member throttle
             * @return Reference to member throttle
             */
            eProsima_user_DllExport float& throttle();

            /*!
             * @brief This function sets a value in member steer
             * @param _steer New value for member steer
             */
            eProsima_user_DllExport void steer(
                    float _steer);

            /*!
             * @brief This function returns the value of member steer
             * @return Value of member steer
             */
            eProsima_user_DllExport float steer() const;

            /*!
             * @brief This function returns a reference to member steer
             * @return Reference to member steer
             */
            eProsima_user_DllExport float& steer();

            /*!
             * @brief This function sets a value in member brake
             * @param _brake New value for member brake
             */
            eProsima_user_DllExport void brake(
                    float _brake);

            /*!
             * @brief This function returns the value of member brake
             * @return Value of member brake
             */
            eProsima_user_DllExport float brake() const;

            /*!
             * @brief This function returns a reference to member brake
             * @return Reference to member brake
             */
            eProsima_user_DllExport float& brake();

            /*!
             * @brief This function sets a value in member hand_brake
             * @param _hand_brake New value for member hand_brake
             */
            eProsima_user_DllExport void hand_brake(
                    bool _hand_brake);

            /*!
             * @brief This function returns the value of member hand_brake
             * @return Value of member hand_brake
             */
            eProsima_user_DllExport bool hand_brake() const;

            /*!
             * @brief This function returns a reference to member hand_brake
             * @return Reference to member hand_brake
             */
            eProsima_user_DllExport bool& hand_brake();

            /*!
             * @brief This function sets a value in member reverse
             * @param _reverse New value for member reverse
             */
            eProsima_user_DllExport void reverse(
                    bool _reverse);

            /*!
             * @brief This function returns the value of member reverse
             * @return Value of member reverse
             */
            eProsima_user_DllExport bool reverse() const;

            /*!
             * @brief This function returns a reference to member reverse
             * @return Reference to member reverse
             */
            eProsima_user_DllExport bool& reverse();

            /*!
             * @brief This function sets a value in member gear
             * @param _gear New value for member gear
             */
            eProsima_user_DllExport void gear(
                    int32_t _gear);

            /*!
             * @brief This function returns the value of member gear
             * @return Value of member gear
             */
            eProsima_user_DllExport int32_t gear() const;

            /*!
             * @brief This function returns a reference to member gear
             * @return Reference to member gear
             */
            eProsima_user_DllExport int32_t& gear();

            /*!
             * @brief This function sets a value in member manual_gear_shift
             * @param _manual_gear_shift New value for member manual_gear_shift
             */
            eProsima_user_DllExport void manual_gear_shift(
                    bool _manual_gear_shift);

            /*!
             * @brief This function returns the value of member manual_gear_shift
             * @return Value of member manual_gear_shift
             */
            eProsima_user_DllExport bool manual_gear_shift() const;

            /*!
             * @brief This function returns a reference to member manual_gear_shift
             * @return Reference to member manual_gear_shift
             */
            eProsima_user_DllExport bool& manual_gear_shift();


            /*!
            * @brief This function returns the maximum serialized size of an object
            * depending on the buffer alignment.
            * @param current_alignment Buffer alignment.
            * @return Maximum serialized size.
            */
            eProsima_user_DllExport static size_t getMaxCdrSerializedSize(
                    size_t current_alignment = 0);

            /*!
             * @brief This function returns the serialized size of a data depending on the buffer alignment.
             * @param data Data which is calculated its serialized size.
             * @param current_alignment Buffer alignment.
             * @return Serialized size.
             */
            eProsima_user_DllExport static size_t getCdrSerializedSize(
                    const carla_msgs::msg::CarlaEgoVehicleControl& data,
                    size_t current_alignment = 0);


            /*!
             * @brief This function serializes an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void serialize(
                    eprosima::fastcdr::Cdr& cdr) const;

            /*!
             * @brief This function deserializes an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void deserialize(
                    eprosima::fastcdr::Cdr& cdr);



            /*!
             * @brief This function returns the maximum serialized size of the Key of an object
             * depending on the buffer alignment.
             * @param current_alignment Buffer alignment.
             * @return Maximum serialized size.
             */
            eProsima_user_DllExport static size_t getKeyMaxCdrSerializedSize(
                    size_t current_alignment = 0);

            /*!
             * @brief This function tells you if the Key has been defined for this type
             */
            eProsima_user_DllExport static bool isKeyDefined();

            /*!
             * @brief This function serializes the key members of an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void serializeKey(
                    eprosima::fastcdr::Cdr& cdr) const;

        private:

            std_msgs::msg::Header m_header;
            float m_throttle;
            float m_steer;
            float m_brake;
            bool m_hand_brake;
            bool m_reverse;
            int32_t m_gear;
            bool m_manual_gear_shift;

        };
    } // namespace msg
} // namespace carla_msgs

#endif // _FAST_DDS_GENERATED_CARLA_MSGS_MSG_CARLAEGOCarlaEgoVehicleControl_H_
