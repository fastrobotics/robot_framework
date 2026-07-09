/**
 * @file JoystickMapper.hpp
 * @author David Gitz
 * @brief
 * @version 0.1
 * @date 2026-07-08
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <JoyMsg.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    /**
     * @brief Maps Raw Joystick Data to a common definition.
     * @details
     *
     */
    class JoystickMapper {
       public:
        static constexpr uint8_t AXIS_COUNT = 3;  //!< The number of Axis that the Mapped Joystick will always have.
        /**
         * @brief Process a Joystick Message
         *
         * @param joy
         * @return fast::rf::messages::SensorMsgs::JoyMsg
         */
        fast::rf::messages::SensorMsgs::JoyMsg new_joy(fast::rf::messages::SensorMsgs::JoyMsg joy);
    };

}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem