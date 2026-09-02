/**
 * @file IArmedStateManagerProcess.hpp
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
#include <ArmStateChangeSrv.hpp>
#include <DiagnosticMsg.hpp>
#include <IProcess.hpp>
#include <Infrastructure/Logger.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>

namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager {
    struct ArmedStateManagerProcessConfig {
        uint8_t expected_arm_signals{0};
        bool is_ok() {
            if (expected_arm_signals == 0) {
                fast::rf::Logger::logError("Config is Invalid: " + pretty());
                return false;
            }
            return true;
        }
        std::string pretty() {
            std::string str = "Config: \n";
            str += "\tExpected Arm Signals: " + std::to_string(expected_arm_signals) + "\n";
            return str;
        }
    };

    /**
     * @brief Interface for the ArmedStateManager Process
     *
     */
    class IArmedStateManagerProcess : public fast::rf::IProcess {
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
         * @brief Set the config
         *
         * @param config
         * @return true
         * @return false
         */
        virtual bool set_config(ArmedStateManagerProcessConfig config) = 0;

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
    };
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager
