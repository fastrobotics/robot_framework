/**
 * @file ArmCommandMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-17
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <RobotFrameworkDefinitions.hpp>
namespace fast::rf::messages::InfrastructureMsgs {
    /**
     * @brief ArmCommandMsg Definition
     *
     */
    struct ArmCommandMsg {
        fast::rf::ArmedState armed_state;  //!< The Armed State to command for the entire Robot.
        ArmCommandMsg() : armed_state(fast::rf::ArmedState::UNKNOWN) {}
    };
}  // namespace fast::rf::messages::InfrastructureMsgs
