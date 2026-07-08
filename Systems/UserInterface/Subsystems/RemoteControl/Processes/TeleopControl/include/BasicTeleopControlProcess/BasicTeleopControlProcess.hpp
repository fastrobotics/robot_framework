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

namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    /**
     * @brief Minimal Implementation for a TeleopControl Process
     *
     */
    class BasicTeleopControlProcess : public BaseTeleopControlProcess {
       public:
        static constexpr double DEFAULT_STEP =
            10.0;  //!< Default value for step change between arrow keys pressed (i.e. the amount that each arrow key
                   //!< press will change the output)
        static constexpr double MAX_VALUE =
            100.0;  //!< Default value for max (and -1.0*max for min values) for max output checks.
        BasicTeleopControlProcess() : BaseTeleopControlProcess() {}

        /**
         * @brief Initialize the Object
         *
         * @return true
         * @return false
         */
        bool init() override;

        /**
         * @brief Set the config object
         *
         * @param forward_velocity_x_step_change Should be between Max Forward and Max Reverse Velocities.  Should be a
         * positive number.
         * @param angular_velocity_z_step_change Should be between Max Angular ans Min Angular Velocities.  Should be a
         * positive number.
         * @param max_forward_x_velocity Max Forward Velocity should be higher than Max Reverse Velocity
         * @param max_reverse_x_velocity Max Reverse Velocity should be lower than Max Forward Velocity
         * @param max_angular_z_velocity Max Angular Velocity should be higher than Min Angular Velocity
         * @param min_angular_z_velocity Min Angular Velocity should be lower than Max Angular Velocity
         * @return true
         * @return false
         */
        bool set_config(double forward_velocity_x_step_change, double angular_velocity_z_step_change,
                        double max_forward_x_velocity, double max_reverse_x_velocity, double max_angular_z_velocity,
                        double min_angular_z_velocity);

        /**
         * @brief Update with recent timing data
         *
         * @param current_time_sec
         * @param delta_time_sec
         * @return true If update executed ok
         * @return false If update executed with some error
         */
        bool update(double current_time_sec, double delta_time_sec) override;

        /**
         * @brief Process a key
         *
         * @param key
         * @return true
         * @return false
         */
        bool key_pressed(KeyPressed key);

       private:
        double forward_velocity_x_step_change_{DEFAULT_STEP};
        double angular_velocity_z_step_change_{DEFAULT_STEP};
        double max_forward_x_velocity_{MAX_VALUE};
        double max_reverse_x_velocity_{-1.0 * MAX_VALUE};
        double max_angular_z_velocity_{MAX_VALUE};
        double min_angular_z_velocity_{-1.0 * MAX_VALUE};
    };
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem