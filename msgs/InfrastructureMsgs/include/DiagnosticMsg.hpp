/**
 * @file DiagnosticMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-01
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <RobotFrameworkDefinitions.hpp>
#include <cstdint>
#include <string>
namespace fast::rf::messages::InfrastructureMsgs {
    /**
     * @brief Diagnostic Message Definition
     *
     */
    struct DiagnosticMsg {
        uint8_t systemID;                                               //!< Unique Identifier for System
        uint8_t subsystemID;                                            //!< Unique Identifier for the Subsystem
        uint8_t processID;                                              //!< Unique Identifier for the Process
        fast::rf::DiagnosticDefinition::DiagnosticType diagnosticType;  //!< Unique Identifier for the Diagnostic Type
        fast::rf::Level level;                                          //!< Level
        fast::rf::DiagnosticDefinition::DiagnosticMessage
            diagnosticMessage;  //!< Unique Identifier for the Diagnostic Message

        std::string description;  //!< Description of the Diagnostic
        /**
         * @brief Construct a new Diagnostic Msg object
         *
         * @param systemID
         * @param subsystemID
         * @param processID
         */
        DiagnosticMsg(uint8_t systemID, uint8_t subsystemID, uint8_t processID,
                      fast::rf::DiagnosticDefinition::DiagnosticType diagnosticType)
            : systemID(systemID),
              subsystemID(subsystemID),
              processID(processID),
              diagnosticType(diagnosticType),
              level(fast::rf::Level::INFO),
              diagnosticMessage(fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING),
              description("Initializing Diagnostic"){};

        std::string pretty() {
            std::string str = std::to_string(systemID) + "-" + std::to_string(subsystemID) + "-" +
                              std::to_string(processID) + " " + fast::rf::DiagnosticDefinition::pretty(diagnosticType) +
                              " Level: " + fast::rf::pretty(level) + " " +
                              fast::rf::DiagnosticDefinition::pretty(diagnosticMessage) + " " + description;
            return str;
        }
    };
}  // namespace fast::rf::messages::InfrastructureMsgs
