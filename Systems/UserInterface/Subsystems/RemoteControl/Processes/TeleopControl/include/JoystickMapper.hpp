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
#include <ITeleopControlProcess.hpp>
#include <JoyMsg.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem::TeleopControl {
    /**
     * @brief Maps Raw Joystick Data to a common definition.
     * @details
     *
     */
    class JoystickMapper {
       public:
        /**
         * @brief Initialize the object
         *
         * @param device What type of device will be used
         * @return true
         * @return false
         */
        bool init(ControlDevice device);
        static constexpr uint8_t AXIS_COUNT = 3;  //!< The number of Axis that the Mapped Joystick will always have.
        /**
         * @brief Process a Joystick Message
         *
         * @param joy
         * @return fast::rf::messages::SensorMsgs::JoyMsg
         */
        fast::rf::messages::SensorMsgs::JoyMsg new_joy(fast::rf::messages::SensorMsgs::JoyMsg joy);

       private:
        ControlDevice control_device{ControlDevice::UNKNOWN};  //!< The device being used
        bool is_initialized{false};                            // If the object is initialized
    };

}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem::TeleopControl