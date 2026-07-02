/**
 * @file BaseDriveExecutorProcess.hpp
 * @author yDavid Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IDriveExecutorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
    /**
     * @brief Base DriveExecutor Process
      @details Concrete DriveExecutor Processes should derive from this
     *
     */
    class BaseDriveExecutorProcess : public IDriveExecutorProcess {
       public:
        /**
         * @brief Construct a new Base DriveExecutor Process object
         *
         */
        BaseDriveExecutorProcess()
            : diagnostic(fast::rf::NavigationSystem::SYSTEM_ID,
                         fast::rf::NavigationSystem::NavigationExecutorSubsystem::SUBSYSTEM_ID,
                         fast::rf::NavigationSystem::NavigationExecutorSubsystem::PROCESS_DRIVE_EXECUTOR_ID) {}

        /**
         * @brief Get the diagnostic object
         *
         * @return fast::rf::messages::InfrastructureMsgs::DiagnosticMsg
         */
        fast::rf::messages::InfrastructureMsgs::DiagnosticMsg get_diagnostic() override { return diagnostic; }
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

       protected:
        double current_time_sec_{-1.0};                                    //!< Current system time
        fast::rf::messages::InfrastructureMsgs::DiagnosticMsg diagnostic;  //!< Holds current diagnostic
    };
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem