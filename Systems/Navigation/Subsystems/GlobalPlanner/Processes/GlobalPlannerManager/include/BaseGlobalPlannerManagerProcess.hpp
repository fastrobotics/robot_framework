/**
 * @file BaseGlobalPlannerManagerProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <IGlobalPlannerManagerProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>
namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem {
    /**
     * @brief Base GlobalPlannerManager Process
      @details Concrete GlobalPlannerManager Processes should derive from this
     *
     */
    class BaseGlobalPlannerManagerProcess : public IGlobalPlannerManagerProcess {
       public:
        /**
         * @brief Construct a new Base GlobalPlannerManager Process object
         *
         */
        BaseGlobalPlannerManagerProcess()
            : diagnosticManager(fast::rf::NavigationSystem::SYSTEM_ID,
                                fast::rf::NavigationSystem::GlobalPlannerSubsystem::SUBSYSTEM_ID,
                                fast::rf::NavigationSystem::GlobalPlannerSubsystem::PROCESS_GLOBALPLANNER_MANAGER_ID) {}
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

       protected:
        double current_time_sec_{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
    };
}  // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem