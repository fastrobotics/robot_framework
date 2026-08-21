/**
 * @file BasicTrajectoryControllerProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <BaseTrajectoryControllerProcess.hpp>
#include <Controller/PIDController/PIDController.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController {
    class BasicTrajectoryControllerConfig {
       public:
        bool set_pid_controller_config(fast::rf::NavigationSystem::Controller::PIDControllerConfig pid_config) {
            bool status = pid_config_.is_ok();
            if (status == false) {
                return false;
            }
            pid_config_ = pid_config;
            return true;
        }
        fast::rf::NavigationSystem::Controller::PIDControllerConfig get_pid_controller_config() { return pid_config_; }
        std::string pretty() { return pid_config_.pretty(); }
        bool is_ok() {
            bool status = pid_config_.is_ok();
            return status;
        }

       private:
        fast::rf::NavigationSystem::Controller::PIDControllerConfig pid_config_;
    };
    /**
     * @brief Minimal implementation for a TrajectoryController Process
     *
     */
    class BasicTrajectoryControllerProcess : public BaseTrajectoryControllerProcess {
       public:
        BasicTrajectoryControllerProcess() : BaseTrajectoryControllerProcess() {}

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
         * @param config
         * @return true
         * @return false
         */
        bool set_config(BasicTrajectoryControllerConfig config);
        /**
         * @brief Update with recent timing data
         *
         * @param current_time_sec
         * @return true If update executed ok
         * @return false If update executed with some error
         */
        bool update(double current_time_sec) override;

        /**
         * @brief Human readable string
         *
         * @return std::string
         */
        std::string pretty() override;

        /**
         * @brief Process a new pose
         *
         * @param pose
         * @return true
         * @return false
         */
        bool new_pose(fast::rf::messages::GeometryMsgs::OdomMsg pose) override;

        /**
         * @brief Process a new desired command
         *
         * @param cmd
         * @return true
         * @return false
         */
        bool new_desired_command(fast::rf::messages::GeometryMsgs::TwistMsg cmd) override;

       private:
        BasicTrajectoryControllerConfig config_;
    };
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController