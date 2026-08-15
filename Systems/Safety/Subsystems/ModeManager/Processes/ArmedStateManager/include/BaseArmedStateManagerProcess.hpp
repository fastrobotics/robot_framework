/**
 * @file BaseArmedStateManagerProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IArmedStateManagerProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>
namespace fast::rf::SafetySystem::ModeManagerSubsystem {
    /**
     * @brief Base ArmedStateManager Process
      @details Concrete ArmedStateManager Processes should derive from this
     *
     */
    class BaseArmedStateManagerProcess : public IArmedStateManagerProcess {
       public:
        /**
         * @brief Construct a new Base ArmedStateManager Process object
         *
         */
        BaseArmedStateManagerProcess()
            : diagnosticManager(fast::rf::SafetySystem::SYSTEM_ID,
                                fast::rf::SafetySystem::ModeManagerSubsystem::SUBSYSTEM_ID,
                                fast::rf::SafetySystem::ModeManagerSubsystem::PROCESS_ARMEDSTATEMANAGER_ID),
              ready_to_arm(fast::rf::SafetySystem::SYSTEM_ID,
                           fast::rf::SafetySystem::ModeManagerSubsystem::SUBSYSTEM_ID,
                           fast::rf::SafetySystem::ModeManagerSubsystem::PROCESS_ARMEDSTATEMANAGER_ID) {}
        /**
         * @brief Update the base object
         *
         * @param current_time_sec
         * @return true If ok
         * @return false If not ok
         */
        virtual bool update(double current_time_sec);

        /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
            return diagnosticManager.get_diagnostics();
        }

        /**
         * @brief Pretty print the Process
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
        double current_time_sec{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;  //!< Ready to Arm object
    };
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem