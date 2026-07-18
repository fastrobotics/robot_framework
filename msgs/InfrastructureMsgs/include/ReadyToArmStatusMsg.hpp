/**
 * @file ReadyToArmStatusMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-17
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <cstdint>
namespace fast::rf::messages::InfrastructureMsgs {
    /**
     * @brief ReadyToArmStatusMsg Definition
     *
     */
    struct ReadyToArmStatusMsg {
        uint8_t systemID;     //!< Unique Identifier for System
        uint8_t subsystemID;  //!< Unique Identifier for the Subsystem
        uint8_t processID;    //!< Unique Identifier for the Process
        bool ready_to_arm;    //!< If the Process is Ready to Arm
        ReadyToArmStatusMsg() {}

        /**
         * @brief Construct a new Ready To Arm Status Msg object
         *
         * @param systemID
         * @param subsystemID
         * @param processID
         */
        ReadyToArmStatusMsg(uint8_t systemID, uint8_t subsystemID, uint8_t processID)
            : systemID(systemID), subsystemID(subsystemID), processID(processID), ready_to_arm(false){};
    };
}  // namespace fast::rf::messages::InfrastructureMsgs
