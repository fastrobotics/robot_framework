/**
 * @file IArmedStateManagerProcess.hpp
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
#include <ArmStateChangeSrv.hpp>
#include <DiagnosticMsg.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>

namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager {
    /**
     * @brief Interface for the ArmedStateManager Process
     *
     */
    class IArmedStateManagerProcess {
       public:
        IArmedStateManagerProcess() = default;
        virtual ~IArmedStateManagerProcess() = default;

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
        virtual std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() = 0;

        /**
         * @brief Request an Arm State Change
         *
         * @param request
         * @return fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse
         */
        virtual fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse
        request_armstate_change(
            fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest request) = 0;

        /**
         * @brief Provide a new Ready to Arm Status
         *
         * @param msg
         * @return true
         * @return false
         */
        virtual bool new_ReadyToArmStatus(fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg msg) = 0;

        /**
         * @brief Get the ArmCommandMsg object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ArmCommandMsg
         */
        virtual fast::rf::messages::InfrastructureMsgs::ArmCommandMsg get_ArmCommandMsg() = 0;

        virtual fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() = 0;
    };
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager