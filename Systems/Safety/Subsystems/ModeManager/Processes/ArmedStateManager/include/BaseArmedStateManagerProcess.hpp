/**
 * @file BaseArmedStateManagerProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-BaseHeader v0.1
 */
#pragma once
#include <IArmedStateManagerProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <Infrastructure/Logger.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>
namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager {
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
            : m_systemId(fast::rf::SafetySystem::SYSTEM_ID),
              m_subSystemId(fast::rf::SafetySystem::ModeManagerSubsystem::SUBSYSTEM_ID),
              m_processId(
                  fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager::PROCESS_ARMEDSTATEMANAGER_ID),
              m_diagnosticManager(m_systemId, m_subSystemId, m_processId),
              ready_to_arm(m_systemId, m_subSystemId, m_processId) {}

        /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
            return m_diagnosticManager.getDiagnostics();
        }

        /**
         * @brief Get the ready to arm object
         * @todo Process should report ready to arm for itself, when all ready to arm signals are good to go.  Do this
         * during AB#1846.
         * @return fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg
         */
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() override { return ready_to_arm; }

       protected:
        bool set_config(ArmedStateManagerProcessConfig config) override {
            if (config.is_ok() == false) {
                fast::rf::Logger::logError("Config is not Valid: " + config.pretty());
                return false;
            }
            config_ = config;
            return true;
        }

        /**
         * @brief Get the System Id object
         *
         * @return uint8_t
         */
        uint8_t getSystemId() override { return m_systemId; }
        /**
         * @brief Get the Sub System Id object
         *
         * @return uint8_t
         */
        uint8_t getSubSystemId() override { return m_subSystemId; }
        /**
         * @brief Get the Process Id object
         *
         * @return uint8_t
         */
        uint8_t getProcessId() override { return m_processId; }

        /**
         * @brief Update the base object
         *
         * @param currentTimeSec
         * @return true If ok
         * @return false If not ok
         */
        virtual bool update(double currentTimeSec);
        /**
         * @brief Pretty print the Process
         *
         * @return std::string
         */
        virtual std::string pretty();
        uint8_t m_systemId{0};
        uint8_t m_subSystemId{0};
        uint8_t m_processId{0};
        ArmedStateManagerProcessConfig config_;  //!< Process Config
        double m_currentTimeSec{-1.0};           //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            m_diagnosticManager;  //!< Entity responsible for managing diagnostics.
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;  //!< Ready to Arm object
       private:
    };
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager
