/**
 * @file BasicTeleopControlProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <BaseTeleopControlProcess.hpp>
#include <BasicTeleopControlProcess/TwistComputer.hpp>
#include <JoyMsg.hpp>

namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    /**
     * @brief Minimal Implementation for a TeleopControl Process
     *
     */
    class BasicTeleopControlProcess : public BaseTeleopControlProcess {
       public:
        BasicTeleopControlProcess() : BaseTeleopControlProcess() {}

        /**
         * @brief Initialize the object
         *
         * @param device The controller device
         * @return true
         * @return false
         */
        bool init(ControlDevice device) override;

        /**
         * @brief Set the config object
         *
         * @param max_forward_x_velocity Max Forward Velocity should be higher than Max Reverse Velocity
         * @param max_reverse_x_velocity Max Reverse Velocity should be lower than Max Forward Velocity
         * @param max_angular_z_velocity Max Angular Velocity should be higher than Min Angular Velocity
         * @param min_angular_z_velocity Min Angular Velocity should be lower than Max Angular Velocity
         * @return true
         * @return false
         */
        bool set_config(double max_forward_x_velocity, double max_reverse_x_velocity, double max_angular_z_velocity,
                        double min_angular_z_velocity) {
            return twist_computer.set_config(max_forward_x_velocity, max_reverse_x_velocity, max_angular_z_velocity,
                                             min_angular_z_velocity);
        }

        /**
         * @brief Update with recent timing data
         *
         * @param current_time_sec
         * @return true If update executed ok
         * @return false If update executed with some error
         */
        bool update(double current_time_sec) override;

        /**
         * @brief Process a new Joystick Message
         *
         * @param joy
         * @return true
         * @return false
         */
        bool new_joy(fast::rf::messages::SensorMsgs::JoyMsg joy);

       private:
        TwistComputer twist_computer;
    };
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem