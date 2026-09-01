/**
 * @file IDriveExecutorProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-Interface
 */
#pragma once
#include <DiagnosticMsg.hpp>
#include <IDriveExecutorOutput.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <TwistMsg.hpp>
#include <vector>

using namespace fast::rf::messages;
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor {
    /**
     * @brief Interface for the DriveExecutor Process
     *
     */
    class IDriveExecutorProcess {
       public:
        IDriveExecutorProcess() = default;
        virtual ~IDriveExecutorProcess() = default;

        /**
         * @brief Initialize the object
         *
         * @return true
         * @return false
         */
        virtual bool init() = 0;
        /**
         * @brief Generic Update function
         *
         * @param current_time_sec Current time stamp
         * @return true If the process updated ok
         * @return false If the process did not update ok
         */
        virtual bool update(double current_time_sec) = 0;

        /**
         * @brief Generic Function for Drive Executor to process
         *
         * @param cmd Command to process
         * @return IDriveExecutorOutput* Abstract type
         */

        virtual IDriveExecutorOutput* new_cmd(GeometryMsgs::TwistMsg cmd) = 0;

        /**
         * @brief Get the most recent output
         *
         * @return IDriveExecutorOutput*
         */
        virtual IDriveExecutorOutput* get_output() = 0;
        /**
         * @brief Get the diagnostic object
         *
         * @return fast::rf::messages::InfrastructureMsgs::DiagnosticMsg
         */
        virtual std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() = 0;

        /**
         * @brief Pretty print current status of object
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
    };
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor