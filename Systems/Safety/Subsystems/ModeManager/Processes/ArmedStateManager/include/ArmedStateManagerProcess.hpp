/**
 * @file ArmedStateManagerProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <ArmStateCommander.hpp>
#include <BaseArmedStateManagerProcess.hpp>
#include <ReadyToArmComputer.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager {
    struct Test {};
    /**
     * @brief Minimal Implementation for a ArmedStateManager Process
     *
     */
    class ArmedStateManagerProcess : public BaseArmedStateManagerProcess {
       public:
        ArmedStateManagerProcess() : BaseArmedStateManagerProcess() {}

        /**
         * @brief Initialize the Object
         *
         * @return true
         * @return false
         */
        bool init() override;

        bool set_config(ArmedStateManagerProcessConfig config) override {
            if (BaseArmedStateManagerProcess::set_config(config) == false) {
                return false;
            }
            // GCOV_EXCL_START
            // Base class is already checking this, so a little redundant until more data is added.  Keep as a
            // safe-guard.
            if (ready_to_arm_computer.set_config(config.expected_arm_signals) == false) {
                return false;
            }
            // GCOV_EXCL_STOP
            return true;
        }

        /**
         * @brief Update with recent timing data
         *
         * @param current_time_sec
         * @return true If update executed ok
         * @return false If update executed with some error
         */
        bool update(double current_time_sec) override;

        /**
         * @brief Human readable string
         *
         * @return std::string
         */
        std::string pretty() override;

        /**
         * @brief Request an Arm State Change
         *
         * @param request
         * @return fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse
         */
        fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse request_armstate_change(
            fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest request) override;

        /**
         * @brief Provide a new Ready to Arm Status
         *
         * @param msg
         * @return true
         * @return false
         */
        bool new_ReadyToArmStatus(fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg msg) override;

        /**
         * @brief Get the ArmCommandMsg object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ArmCommandMsg
         */
        fast::rf::messages::InfrastructureMsgs::ArmCommandMsg get_ArmCommandMsg() override {
            return arm_state_commander.get_ArmCommandMsg();
        }

       private:
        ArmStateCommander arm_state_commander;
        ReadyToArmComputer ready_to_arm_computer;
    };
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager