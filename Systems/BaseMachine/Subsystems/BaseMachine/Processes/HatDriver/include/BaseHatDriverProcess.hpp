/**
 * @file BaseHatDriverProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IHatDriverProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem {
    /**
     * @brief Base HatDriver Process
      @details Concrete HatDriver Processes should derive from this
     *
     */
    class BaseHatDriverProcess : public IHatDriverProcess {
       public:
        /**
         * @brief Construct a new Base HatDriver Process object
         *
         */
        BaseHatDriverProcess()
            : diagnosticManager(fast::rf::BaseMachineSystem::SYSTEM_ID,
                                fast::rf::BaseMachineSystem::BaseMachineSubsystem::SUBSYSTEM_ID,
                                fast::rf::BaseMachineSystem::BaseMachineSubsystem::PROCESS_HATDRIVER_ID) {}
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
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
            return diagnosticManager.get_diagnostics();
        }

       protected:
        /**
         * @brief Pretty print the Process
         *
         * @return std::string
         */
        std::string base_pretty();
        double current_time_sec_{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
    };
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem