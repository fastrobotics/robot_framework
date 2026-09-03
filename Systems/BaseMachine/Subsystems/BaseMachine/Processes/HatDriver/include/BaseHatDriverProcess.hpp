/**
 * @file BaseHatDriverProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-BaseHeader v0.1
 */
#pragma once
#include <IHatDriverProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <Infrastructure/Logger.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver {
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
            : m_systemId(fast::rf::BaseMachineSystem::SYSTEM_ID),
              m_subSystemId(fast::rf::BaseMachineSystem::BaseMachineSubsystem::SUBSYSTEM_ID),
              m_processId(fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver::PROCESS_HATDRIVER_ID),
              diagnosticManager(m_systemId, m_subSystemId, m_processId),
              ready_to_arm(m_systemId, m_subSystemId, m_processId) {}

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

        bool updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType type, fast::rf::Level level,
                              fast::rf::DiagnosticDefinition::DiagnosticMessage message,
                              std::string description) override {
            return diagnosticManager.updateDiagnostic(type, level, message, description);
        }
        /**
         * @brief Update the Robot Arm Command State
         *
         * @param robot_arm_command
         */
        void update_RobotArmCommand(fast::rf::messages::InfrastructureMsgs::ArmCommandMsg robot_arm_command) override {
            m_robotArmCommand = robot_arm_command;
        }

        /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
            return diagnosticManager.getDiagnostics();
        }

        /**
         * @brief Get the ready to arm object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg
         */
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() override { return ready_to_arm; }

       protected:
        /**
         * @brief Update the base object
         *
         * @param current_time_sec
         * @return true If ok
         * @return false If not ok
         */
        virtual bool update(double current_time_sec);  //!< Base function to update
        /**
         * @brief Pretty print the Process
         *
         * @return std::string
         */
        virtual std::string pretty();
        uint8_t m_systemId{0};
        uint8_t m_subSystemId{0};
        uint8_t m_processId{0};
        double current_time_sec_{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
        fast::rf::messages::InfrastructureMsgs::ArmCommandMsg m_robotArmCommand;   //!< The Robot Arm Command State
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;  //!< Ready to Arm object
    };
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver
