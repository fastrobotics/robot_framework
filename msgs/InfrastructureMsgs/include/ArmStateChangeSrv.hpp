/**
 * @file ArmStateChangeSrv.hpp
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
     * @brief Service to requst an Arm State Change
     *
     */
    struct ArmStateChangeSrv {
        /**
         * @brief The Request
         *
         */
        struct ArmStateChangeSrvRequest {
            fast::rf::ArmedState requested_armed_state;  //!< The requested Arm State
            ArmStateChangeSrvRequest() : requested_armed_state(ArmedState::UNKNOWN) {}
        } request;  //!< The Request
        /**
         * @brief The Response
         *
         */
        struct ArmStateChangeSrvResponse {
            fast::rf::ArmedState
                current_armed_state;  //!< The current Armed State.  Note that this state may not be the requested armed
                                      //!< state, as the state can take time to change.
            bool request_approved;    //!< If the request was approved
            ArmStateChangeSrvResponse() : current_armed_state(ArmedState::UNKNOWN), request_approved(false) {}
        } response;  //!< The Response

        ArmStateChangeSrv() {}
    };
}  // namespace fast::rf::messages::InfrastructureMsgs
