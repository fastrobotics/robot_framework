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
#include <ArmCommandMsg.hpp>
#include <ArmStateChangeSrv.hpp>
#include <DiagnosticMsg.hpp>
#include <JoyMsg.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <TwistMsg.hpp>
#include <cmath>
#include <limits>
#include <string>
#include <vector>

namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem::TeleopControl {
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
     * @brief CalibrationData Structure
     *
     */
    struct JoystickCalibrationData {
        double x_min;              //!< Min X value
        double x_max;              //!< Max X Value
        double x_deadband;         //!< X Deadband
        double y_min;              //!< Min Y Value
        double y_max;              //!< Max Y Value
        double y_deadband;         //!< Y Deadband
        double throttle_min;       //!< Min Throttle
        double throttle_max;       //!< Max Throttle
        double throttle_deadband;  //!< Throttle Deadband
        JoystickCalibrationData() {
            x_deadband = 0.0;
            x_min = INFINITY;
            x_max = -INFINITY;
            y_deadband = 0.0;
            y_min = INFINITY;
            y_max = -INFINITY;
            throttle_min = INFINITY;
            throttle_max = -INFINITY;
            throttle_deadband = 0.0;
        }
        /**
         * @brief Optional Initializer in case you don't want to use a calibration file.
         *
         */
        void optional_init() {
            x_deadband = 0.0;
            x_min = -1.0;
            x_max = 1.0;
            y_deadband = 0.0;
            y_min = -1.0;
            y_max = 1.0;
            throttle_min = -1.0;
            throttle_max = 1.0;
            throttle_deadband = 0.0;
        }
        /**
         * @brief Pretty print joystick dalibration data
         *
         * @return std::string
         */
        std::string pretty() {
            std::string str = "\nX:\n\t DB: " + std::to_string(x_deadband) + " min: " + std::to_string(x_min) +
                              " max: " + std::to_string(x_max) + "\n";
            str += "Y:\n\t DB: " + std::to_string(y_deadband) + " min: " + std::to_string(y_min) +
                   " max: " + std::to_string(y_max) + "\n";
            str += "Thr:\n\t DB: " + std::to_string(throttle_deadband) + " min: " + std::to_string(throttle_min) +
                   " max: " + std::to_string(throttle_max);
            return str;
        }
    };

    /**
     * @brief Interface for the TeleopControl Process
     *
     */
    class ITeleopControlProcess {
       public:
        static constexpr double INPUT_TIMEOUT_SEC =
            5.0;  //!< R/C Input not provided for this duration will trip diagnostics/disable ready to arm

        ITeleopControlProcess() = default;
        virtual ~ITeleopControlProcess() = default;

        /**
         * @brief Initialize the object
         *
         * @param device
         * @param joy_calibration_data
         * @return true
         * @return false
         */
        virtual bool init(ControlDevice device, JoystickCalibrationData joy_calibration_data) = 0;

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
         * @brief Get the armstate change request
         *
         * @return fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest
         */
        virtual fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest
        get_armstate_change_request() = 0;

        /**
         * @brief Set the operation mode object
         *
         * @param mode
         * @return true
         * @return false
         */
        virtual bool set_operation_mode(OperationMode mode) = 0;
    };
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem::TeleopControl