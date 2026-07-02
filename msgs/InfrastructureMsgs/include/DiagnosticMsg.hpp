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
#include <cstdint>
#include <string>

namespace fast::rf::messages::InfrastructureMsgs {
    /**
     * @brief Diagnostic Message Definition
     *
     */
    struct DiagnosticMsg {
        uint8_t systemID;         //!< Unique Identifier for System
        uint8_t subsystemID;      //!< Unique Identifier for the Subsystem
        uint8_t processID;        //!< Unique Identifier for the Process
        uint8_t diagnosticType;   //!< Unique Identifier for the Diagnostic Type
        std::string description;  //!< Description of the Diagnostic
        /**
         * @brief Construct a new Diagnostic Msg object
         *
         * @param systemID
         * @param subsystemID
         * @param processID
         */
        DiagnosticMsg(uint8_t systemID, uint8_t subsystemID, uint8_t processID)
            : systemID(systemID), subsystemID(subsystemID), processID(processID), diagnosticType(0), description(""){};

        /**
         * @brief Construct a new Diagnostic Msg object
         *
         */
        DiagnosticMsg() : systemID(0), subsystemID(0), processID(0), diagnosticType(0), description(""){};
    };
}  // namespace fast::rf::messages::InfrastructureMsgs
