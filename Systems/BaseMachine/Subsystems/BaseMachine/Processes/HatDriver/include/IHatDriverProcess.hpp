/**
 * @file IHatDriverProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-Interface v0.1
 */
#pragma once
#include <ArmCommandMsg.hpp>
#include <DiagnosticMsg.hpp>
#include <IProcess.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>

namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver {
    /**
     * @brief Interface for the HatDriver Process
     *
     */
    class IHatDriverProcess : public fast::rf::IProcess {
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
         * @brief Update Robot Command Armed State
         *
         * @param robot_arm_command
         * @return void
         */
        virtual void update_RobotArmCommand(
            fast::rf::messages::InfrastructureMsgs::ArmCommandMsg robot_arm_command) = 0;
    };
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver
