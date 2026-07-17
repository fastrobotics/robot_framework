/**
 * @file ArmStateCommander.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-17
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <ArmCommandMsg.hpp>
#include <ArmStateChangeSrv.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem {
    /**
     * @brief ArmStateCommander
     * @details Responsible for computing the Arm State of the Robot
     */
    class ArmStateCommander {
       public:
        static constexpr double ARMING_HOLD_TIME =
            5.0f;  //!< How long to hold the Arming State before transition to Armed
        /**
         * @brief Initialize the Object
         *
         * @return true
         * @return false
         */
        bool init();
        /**
         * @brief Get a nice string for the state of the robot
         *
         * @return std::string
         */
        std::string pretty();
        /**
         * @brief Update the Object
         *
         * @param current_time_sec
         * @return true
         * @return false
         */
        bool update(double current_time_sec);
        /**
         * @brief Update the Robot Ready To Arm State
         *
         * @param robot_ready_to_arm This should be a single value representing the entire Ready To Arm state for the
         * Robot
         * @return true
         * @return false
         */
        bool update_ready_to_arm(bool robot_ready_to_arm);
        /**
         * @brief A Service to request an Arm State Change.  Allowed States: ARMED, DISARMED.
         *
         * @param request
         * @return fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse
         */
        fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse request_armstate_change(
            fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest request);
        /**
         * @brief Get the ArmCommandMsg object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ArmCommandMsg
         */
        fast::rf::messages::InfrastructureMsgs::ArmCommandMsg get_ArmCommandMsg() { return arm_command; }

       private:
        bool first_run{true};
        double last_time_sec{-1.0};
        double run_time{0.0};
        fast::rf::messages::InfrastructureMsgs::ArmCommandMsg arm_command;
    };
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem