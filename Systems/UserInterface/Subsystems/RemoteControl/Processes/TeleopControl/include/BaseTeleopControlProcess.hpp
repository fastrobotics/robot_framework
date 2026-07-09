/**
 * @file BaseTeleopControlProcess.hpp
 * @author yDavid Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <ITeleopControlProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <JoystickMapper.hpp>
#include <JoystickScaler.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    /**
     * @brief Base TeleopControl Process
      @details Concrete TeleopControl Processes should derive from this
     *
     */
    class BaseTeleopControlProcess : public ITeleopControlProcess {
       public:
        /**
         * @brief Construct a new Base TeleopControl Process object
         *
         */
        BaseTeleopControlProcess()
            : diagnosticManager(fast::rf::UserInterfaceSystem::SYSTEM_ID,
                                fast::rf::UserInterfaceSystem::RemoteControlSubsystem::SUBSYSTEM_ID,
                                fast::rf::UserInterfaceSystem::RemoteControlSubsystem::PROCESS_TELEOPCONTROL_ID) {}
        /**
         * @brief Update the base object
         *
         * @param current_time_sec
         * @param delta_time_sec
         * @return true If ok
         * @return false If not ok
         */
        bool base_update(double current_time_sec,
                         double delta_time_sec);  //!< Base function to update

        /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
            return diagnosticManager.get_diagnostics();
        }

        /**
         * @brief Get the twist output object
         *
         * @return fast::rf::messages::GeometryMsgs::TwistMsg
         */
        fast::rf::messages::GeometryMsgs::TwistMsg get_twist_output() { return desired_twist; }

        /**
         * @brief Pretty print the Process
         *
         * @return std::string
         */
        std::string pretty() override;

        /**
         * @brief Set the operation mode object
         *
         * @param mode Any operation mode that is not UNKNOWN OR END_OF_LIST is supported.
         * @return true
         * @return false
         */
        bool set_operation_mode(OperationMode mode) {
            if ((mode == OperationMode::UNKNOWN) || (mode == OperationMode::END_OF_LIST)) {
                return false;
            }
            operation_mode = mode;
            return true;
        }

       protected:
        double current_time_sec_{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
        fast::rf::messages::GeometryMsgs::TwistMsg
            desired_twist;                                 //!< Data member representing the most current desired twist
        OperationMode operation_mode{OperationMode::RUN};  //!< Operation Mode of the process
        JoystickMapper mapper;                             //!< Maps Joystick inputs to commmon definition
        JoystickScaler scaler;                             //!< Scales Joystick data to common definition
    };
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem