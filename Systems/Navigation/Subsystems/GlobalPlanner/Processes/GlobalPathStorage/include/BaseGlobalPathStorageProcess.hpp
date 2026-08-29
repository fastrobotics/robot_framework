/**
 * @file BaseGlobalPathStorageProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IGlobalPathStorageProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>
namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem::GlobalPathStorage {
    /**
     * @brief Base GlobalPathStorage Process
      @details Concrete GlobalPathStorage Processes should derive from this
     *
     */
    class BaseGlobalPathStorageProcess : public IGlobalPathStorageProcess {
       public:
        /**
         * @brief Construct a new Base GlobalPathStorage Process object
         *
         */
        BaseGlobalPathStorageProcess()
            : diagnosticManager(fast::rf::NavigationSystem::SYSTEM_ID,
                                fast::rf::NavigationSystem::GlobalPlannerSubsystem::SUBSYSTEM_ID,
                                fast::rf::NavigationSystem::GlobalPlannerSubsystem::GlobalPathStorage::
                                    PROCESS_GLOBALPATH_STORAGE_ID) {}
        /**
         * @brief Update the base object
         *
         * @param current_time_sec
         * @return true If ok
         * @return false If not ok
         */
        bool base_update(double current_time_sec);  //!< Base function to update

        /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
            return diagnosticManager.getDiagnostics();
        }

       protected:
        double current_time_sec_{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
    };
}  // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem::GlobalPathStorage