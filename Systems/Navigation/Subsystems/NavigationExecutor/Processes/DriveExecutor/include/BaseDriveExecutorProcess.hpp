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

namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
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
            : diagnosticManager(fast::rf::NavigationSystem::SYSTEM_ID,
                                fast::rf::NavigationSystem::NavigationExecutorSubsystem::SUBSYSTEM_ID,
                                fast::rf::NavigationSystem::NavigationExecutorSubsystem::PROCESS_DRIVE_EXECUTOR_ID) {}

        /**
         * @brief Update the base object
         *
         * @param current_time_sec
         * @param delta_time_sec
         * @return true If ok
         * @return false If not ok
         */
        bool base_update(double current_time_sec,
                         double delta_time_sec);  //!< Base function to update

        /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
            return diagnosticManager.get_diagnostics();
        }
        /**
         * @brief Pretty print object
         *
         * @return std::string
         */
        std::string pretty() override;

       protected:
        double current_time_sec_{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
    };
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem