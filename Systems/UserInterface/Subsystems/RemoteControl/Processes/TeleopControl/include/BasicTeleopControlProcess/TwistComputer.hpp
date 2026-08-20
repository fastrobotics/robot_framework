/**
 * @file TwistComputer.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-08
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <JoyMsg.hpp>
#include <TwistMsg.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem::TeleopControl {
    /**
     * @brief Converts Joystick Data to a Twist
     *
     */
    class TwistComputer {
       public:
        static constexpr double MAX_VALUE =
            100.0;  //!< Default value for max (and -1.0*max for min values) for max output checks.
        /**
         * @brief Set the config object
         *
         * @param max_forward_x_velocity
         * @param max_reverse_x_velocity
         * @param max_angular_z_velocity
         * @param min_angular_z_velocity
         * @return true
         * @return false
         */
        bool set_config(double max_forward_x_velocity, double max_reverse_x_velocity, double max_angular_z_velocity,
                        double min_angular_z_velocity);

        /**
         * @brief Process a Joystick Message
         *
         * @param joy
         * @return fast::rf::messages::GeometryMsgs::TwistMsg
         */
        fast::rf::messages::GeometryMsgs::TwistMsg new_joy(fast::rf::messages::SensorMsgs::JoyMsg joy);

       private:
        double max_forward_x_velocity_{MAX_VALUE};
        double max_reverse_x_velocity_{-1.0 * MAX_VALUE};
        double max_angular_z_velocity_{MAX_VALUE};
        double min_angular_z_velocity_{-1.0 * MAX_VALUE};
    };
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem::TeleopControl