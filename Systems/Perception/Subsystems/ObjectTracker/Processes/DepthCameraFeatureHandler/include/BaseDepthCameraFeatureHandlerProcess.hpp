/**
 * @file BaseDepthCameraFeatureHandlerProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-BaseHeader v0.1
 */
#pragma once
#include <IDepthCameraFeatureHandlerProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>
namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::DepthCameraFeatureHandler {
    /**
     * @brief Base DepthCameraFeatureHandler Process
      @details Concrete DepthCameraFeatureHandler Processes should derive from this
     *
     */
    class BaseDepthCameraFeatureHandlerProcess : public IDepthCameraFeatureHandlerProcess {
       public:
        /**
         * @brief Construct a new Base DepthCameraFeatureHandler Process object
         *
         */
        BaseDepthCameraFeatureHandlerProcess()
            : m_systemId(fast::rf::PerceptionSystem::SYSTEM_ID),
              m_subSystemId(fast::rf::PerceptionSystem::ObjectTrackerSubsystem::SUBSYSTEM_ID),
              m_processId(fast::rf::PerceptionSystem::ObjectTrackerSubsystem::DepthCameraFeatureHandler::
                              PROCESS_DEPTHCAMERAFEATUREHANDLER_ID),
              m_diagnosticManager(m_systemId, m_subSystemId, m_processId),
              m_readyToArm(m_systemId, m_subSystemId, m_processId) {}

        /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>o
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() override = 0;

        /**
         * @brief Get the ready to arm object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg
         */
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() override { return m_readyToArm; }

       protected:
        /**
         * @brief Initialize the base object.  Called by Concrete Function.
         *
         * @return true
         * @return false
         */
        bool init() override = 0;

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
         * @brief Update the base object.  Called by Concrete Function.
         *
         * @param currentTimeSec
         * @return true If ok
         * @return false If not ok
         */
        bool update(double currentTimeSec) override = 0;  //!< Base function to update
        bool updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType type, fast::rf::Level level,
                              fast::rf::DiagnosticDefinition::DiagnosticMessage message,
                              std::string description) override {
            return m_diagnosticManager.updateDiagnostic(type, level, message, description);
        }
        /**
         * @brief Pretty print the Process.  Called by concrete object.
         *
         * @return std::string
         */
        std::string pretty() override = 0;
        double getCurrentTimeSec() { return m_currentTimeSec; }

        fast::rf::core::infrastructure::DiagnosticManager getDiagnosticManager() { return m_diagnosticManager; }

        bool initializeDiagnostics(std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types);

        uint8_t m_systemId{0};
        uint8_t m_subSystemId{0};
        uint8_t m_processId{0};
        double m_currentTimeSec{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            m_diagnosticManager;  //!< Entity responsible for managing diagnostics.
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg m_readyToArm;  //!< Ready to Arm object
    };
}  // namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::DepthCameraFeatureHandler
