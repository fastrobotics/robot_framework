/**
 * @file DiagnosticManager.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-02
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <DiagnosticMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <cstdint>
#include <map>
#include <vector>
namespace fast::rf::core::infrastructure {
    /**
     * @brief A Class to manage Diagnostics
     *
     */
    class DiagnosticManager {
       public:
        /**
         * @brief Construct a new Diagnostic Manager object
         *
         * @param systemId
         * @param subsystemId
         * @param processId
         */
        DiagnosticManager(uint8_t systemId, uint8_t subsystemId, uint8_t processId)
            : m_systemId(systemId), m_subsystemId(subsystemId), m_processId(processId) {}

        /**
         * @brief Destroy the Diagnostic Manager object
         *
         */
        virtual ~DiagnosticManager() = default;
        /**
         * @brief Check if initialized
         *
         * @return true
         * @return false
         */
        bool isInitialized() { return m_initialized; }

        /**
         * @brief Initialize a Diagnostic
         * @details All diagnostics will be initialized to an "INITIALIZING" state.
         *
         * @param diagnosticTypes
         * @return true
         * @return false
         */
        bool initializeDiagnostics(std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes);

        /**
         * @brief Update a diagnostic
         *
         * @param type The Diagnostic type
         * @param level The level of the Diagnostic
         * @param message The specific diagnostic message
         * @param description Human readable text describing the diagnostic
         * @return true
         * @return false
         */
        bool updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType type, fast::rf::Level level,
                              fast::rf::DiagnosticDefinition::DiagnosticMessage message, std::string description);

        /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics();

        /**
         * @brief Get the text of the Diagnostic Manager in a human readable string
         *
         * @return std::string
         */
        std::string pretty();

        /**
         * @brief  Get all diagnostics at or above the Level
         *
         * @param level
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics(fast::rf::Level level);

       private:
        uint8_t m_systemId;
        uint8_t m_subsystemId;
        uint8_t m_processId;
        bool m_initialized{false};
        std::map<fast::rf::DiagnosticDefinition::DiagnosticType, fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
            m_diagnosticMap;
    };
}  // namespace fast::rf::core::infrastructure