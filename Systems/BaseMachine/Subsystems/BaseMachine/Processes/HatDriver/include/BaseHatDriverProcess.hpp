/**
 * @file BaseHatDriverProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IHatDriverProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver {
    /**
     * @brief Base HatDriver Process
      @details Concrete HatDriver Processes should derive from this
     *
     */
    class BaseHatDriverProcess : public IHatDriverProcess {
       public:
        /**
         * @brief Construct a new Base HatDriver Process object
         *
         */
        BaseHatDriverProcess()
            : diagnosticManager(fast::rf::BaseMachineSystem::SYSTEM_ID,
                                fast::rf::BaseMachineSystem::BaseMachineSubsystem::SUBSYSTEM_ID,
                                fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver::PROCESS_HATDRIVER_ID),
              ready_to_arm(fast::rf::BaseMachineSystem::SYSTEM_ID,
                           fast::rf::BaseMachineSystem::BaseMachineSubsystem::SUBSYSTEM_ID,
                           fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver::PROCESS_HATDRIVER_ID) {}
        /**
         * @brief Update the base object
         *
         * @param current_time_sec
         * @return true If ok
         * @return false If not ok
         */
        virtual bool update(double current_time_sec);  //!< Base function to update

        /**
         * @brief Update the Robot Arm Command State
         *
         * @param robot_arm_command_
         */
        void update_RobotArmCommand(fast::rf::messages::InfrastructureMsgs::ArmCommandMsg robot_arm_command_) override {
            robot_arm_command = robot_arm_command_;
        }

        /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
            return diagnosticManager.get_diagnostics();
        }

        /**
         * @brief Get the ready to arm object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg
         */
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() override { return ready_to_arm; }

       protected:
        /**
         * @brief Pretty print the Process
         *
         * @return std::string
         */
        virtual std::string pretty();
        double current_time_sec_{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
        fast::rf::messages::InfrastructureMsgs::ArmCommandMsg robot_arm_command;   //!< The Robot Arm Command State
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;  //!< Ready to Arm object
    };
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver