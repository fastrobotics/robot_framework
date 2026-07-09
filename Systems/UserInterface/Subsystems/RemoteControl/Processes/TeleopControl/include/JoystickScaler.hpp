/**
 * @file JoystickScaler.hpp
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
     * @brief Scales Joystick Data to a common definition
     *
     */
    class JoystickScaler {
       public:
        /**
         * @brief Process a Joystick message
         *
         * @param joy
         * @return fast::rf::messages::SensorMsgs::JoyMsg
         */
        fast::rf::messages::SensorMsgs::JoyMsg new_joy(fast::rf::messages::SensorMsgs::JoyMsg joy);
    };

}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem