/**
 * @file IHatDriverProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <ArmCommandMsg.hpp>
#include <DiagnosticMsg.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>

namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver {
    /**
     * @brief Interface for the HatDriver Process
     *
     */
    class IHatDriverProcess {
       public:
        IHatDriverProcess() = default;
        virtual ~IHatDriverProcess() = default;

        /**
         * @brief Initialize the object
         *
         * @return true
         * @return false
         */
        virtual bool init() = 0;

        /**
         * @brief Generic Update function
         *
         * @param current_time_sec Current time stamp
         * @return true If the process updated ok
         * @return false If the process did not update ok
         */
        virtual bool update(double current_time_sec) = 0;

        /**
         * @brief Update Robot Command Armed State
         *
         * @param robot_arm_command
         * @return void
         */
        virtual void update_RobotArmCommand(
            fast::rf::messages::InfrastructureMsgs::ArmCommandMsg robot_arm_command) = 0;

        /**
         * @brief Pretty print the Process
         *
         * @return std::string
         */
        virtual std::string pretty() = 0;

        /**
         * @brief Get the diagnostic object
         *
         * @return fast::rf::messages::InfrastructureMsgs::DiagnosticMsg
         */
        virtual std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() = 0;

        /**
         * @brief Get the ready to arm object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg
         */
        virtual fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() = 0;
    };
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver