/**
 * @file BaseTrajectorySelectorProcess.hpp
 * @author yDavid Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <ITrajectorySelectorProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
    /**
     * @brief Base TrajectorySelector Process
      @details Concrete TrajectorySelector Processes should derive from this
     *
     */
    class BaseTrajectorySelectorProcess : public ITrajectorySelectorProcess {
       public:
        /**
         * @brief Construct a new Base TrajectorySelector Process object
         *
         */
        BaseTrajectorySelectorProcess()
            : diagnosticManager(
                  fast::rf::NavigationSystem::SYSTEM_ID,
                  fast::rf::NavigationSystem::NavigationExecutorSubsystem::SUBSYSTEM_ID,
                  fast::rf::NavigationSystem::NavigationExecutorSubsystem::PROCESS_TRAJECTORY_SELECTOR_ID) {}
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
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem