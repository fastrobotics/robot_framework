/**
 * @file BaseDriveExecutorProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IDriveExecutorProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>

namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor {
    /**
     * @brief Base DriveExecutor Process
      @details Concrete DriveExecutor Processes should derive from this
     *
     */
    class BaseDriveExecutorProcess : public IDriveExecutorProcess {
       public:
        /**
         * @brief Construct a new Base Drive Executor Process object
         *
         */
        BaseDriveExecutorProcess()
            : diagnosticManager(
                  fast::rf::NavigationSystem::SYSTEM_ID,
                  fast::rf::NavigationSystem::NavigationExecutorSubsystem::SUBSYSTEM_ID,
                  fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor::PROCESS_DRIVE_EXECUTOR_ID),
              ready_to_arm(
                  fast::rf::NavigationSystem::SYSTEM_ID,
                  fast::rf::NavigationSystem::NavigationExecutorSubsystem::SUBSYSTEM_ID,
                  fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor::PROCESS_DRIVE_EXECUTOR_ID) {}

        /**
         * @brief Update the base object
         *
         * @param current_time_sec
         * @return true If ok
         * @return false If not ok
         */
        virtual bool update(double current_time_sec);  //!< Base function to update

        /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
            return diagnosticManager.getDiagnostics();
        }
        /**
         * @brief Pretty print object
         *
         * @return std::string
         */
        virtual std::string pretty();

        /**
         * @brief Get the ready to arm object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg
         */
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() override { return ready_to_arm; }

       protected:
        double current_time_sec_{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;  //!< Ready to Arm object
    };
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor