/**
 * @file ITrajectoryControllerProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <DiagnosticMsg.hpp>
#include <OdomMsg.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <TwistMsg.hpp>
#include <vector>

namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController {
    /**
     * @brief Interface for the TrajectoryController Process
     *
     */
    class ITrajectoryControllerProcess {
       public:
        ITrajectoryControllerProcess() = default;
        virtual ~ITrajectoryControllerProcess() = default;
        /**
         * @brief Initialize the object
         *
         * @return true
         * @return false
         */
        virtual bool init() = 0;
        /**
         * @brief Get the diagnostic object
         *
         * @return fast::rf::messages::InfrastructureMsgs::DiagnosticMsg
         */
        virtual std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() = 0;
        /**
         * @brief Generic Update function
         *
         * @param current_time_sec Current time stamp
         * @return true If the process updated ok
         * @return false If the process did not update ok
         */
        virtual bool update(double current_time_sec) = 0;

        /**
         * @brief Human readable string
         *
         * @return std::string
         */
        virtual std::string pretty() = 0;

        /**
         * @brief Get the ready to arm object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg
         */
        virtual fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() = 0;

        /**
         * @brief Process a new pose
         *
         * @param pose
         * @return true
         * @return false
         */
        virtual bool new_pose(fast::rf::messages::GeometryMsgs::OdomMsg pose) = 0;

        /**
         * @brief Process a new desired command
         *
         * @param cmd
         * @return true
         * @return false
         */
        virtual bool new_desired_command(fast::rf::messages::GeometryMsgs::TwistMsg cmd) = 0;

        /**
         * @brief Get the command data
         *
         * @param cmd
         * @return true if New
         * @return false  if Not
         */
        virtual bool get_command(fast::rf::messages::GeometryMsgs::TwistMsg& cmd) = 0;
    };
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController