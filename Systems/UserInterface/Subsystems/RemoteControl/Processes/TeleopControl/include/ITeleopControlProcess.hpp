/**
 * @file ITeleopControlProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <DiagnosticMsg.hpp>
#include <JoyMsg.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <TwistMsg.hpp>
#include <vector>

namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    /**
     * @brief Enum defining what Control Devices are supported
     *
     */
    enum class ControlDevice {
        UNKNOWN = 0,                //!< Unknown
        THRUSTMASTER_JOYSTICK = 1,  //!< A specific type of Joystick
        END_OF_LIST = 2             //!< Not supported, used for range checks
    };
    /**
     * @brief Set Operation Mode
     *
     */
    enum class OperationMode {
        UNKNOWN = 0,     //!< Unknown
        JOY_TEST = 1,    //!< Test Joystck Mode.  Will not drive output
        RUN = 2,         //!< Normal Operation (Default).
        END_OF_LIST = 3  //!< Not supported, used for range checks
    };

    /**
     * @brief Interface for the TeleopControl Process
     *
     */
    class ITeleopControlProcess {
       public:
        ITeleopControlProcess() = default;
        virtual ~ITeleopControlProcess() = default;

        /**
         * @brief Initialize the object
         *
         * @param device The Controller Device
         * @return true
         * @return false
         */
        virtual bool init(ControlDevice device) = 0;

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
         * @brief Get the ready to arm object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg
         */
        virtual fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() = 0;

        /**
         * @brief Process a Joystick Message
         *
         * @param joy
         * @return true
         * @return false
         */
        virtual bool new_joy(fast::rf::messages::SensorMsgs::JoyMsg joy) = 0;

        /**
         * @brief Get the twist output object
         *
         * @return fast::rf::messages::GeometryMsgs::TwistMsg
         */
        virtual fast::rf::messages::GeometryMsgs::TwistMsg get_twist_output() = 0;

        /**
         * @brief Set the operation mode object
         *
         * @param mode
         * @return true
         * @return false
         */
        virtual bool set_operation_mode(OperationMode mode) = 0;
    };
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem