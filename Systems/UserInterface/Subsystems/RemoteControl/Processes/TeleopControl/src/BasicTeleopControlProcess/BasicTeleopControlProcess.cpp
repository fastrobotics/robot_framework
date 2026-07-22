#include <BasicTeleopControlProcess/BasicTeleopControlProcess.hpp>
#include <Infrastructure/Logger.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {

    bool BasicTeleopControlProcess::init(ControlDevice device) {
        if ((device == ControlDevice::UNKNOWN) && (device == ControlDevice::END_OF_LIST)) {
            fast::rf::Logger::log_error("Unable to initialize an Unknown Control Device.");
            return false;
        }
        bool status = mapper.init(device);
        if (status == false) {
            fast::rf::Logger::log_error("Unable to initialize Joystick Mapper");
            return false;
        }
        status = scaler.init(device);
        if (status == false) {
            fast::rf::Logger::log_error("Unable to initialize Joystick Scaler.");
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL);
        status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        if (status == false) {
            fast::rf::Logger::log_error("Unable to initialize Diagnostics.");
        }

        status = diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL, fast::rf::Level::WARN,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED, "No Joystick Data Yet.");
        return status;
    }
    bool BasicTeleopControlProcess::update(double current_time_sec) {
        bool status = BaseTeleopControlProcess::update(current_time_sec);
        if (status == false) {
            fast::rf::Logger::log_warn("Unable to update!");
            return false;
        }
        status = diagnosticManager.update_diagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE,
                                                     fast::rf::Level::NOERROR,
                                                     fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Ok");
        if (status == false) {
            fast::rf::Logger::log_error("Unable to set Diagnostic.");
            return false;
        }
        return true;
    }
    std::string BasicTeleopControlProcess::pretty() {
        std::string str = "---Basic Telelop Control Process---";
        str += BaseTeleopControlProcess::pretty();
        return str;
    }
    bool BasicTeleopControlProcess::new_joy(fast::rf::messages::SensorMsgs::JoyMsg joy) {
        last_input_time_sec = current_time_sec_;
        bool status = diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Receiving Joystick Data");
        if (status == false) {
            fast::rf::Logger::log_error("Unable to set Diagnostic.");
            return false;
        }
        /**
         * @todo Handle this better during AB#1782
         *
         */
        if (joy.buttons.size() < 2) {
            fast::rf::Logger::log_error("Joystick doesn't have enough buttons!");
            return false;
        }
        if (joy.buttons[1] == 1) {
            if (robot_arm_command.armed_state == fast::rf::ArmedState::DISARMED) {
                armstate_change_request.requested_armed_state = fast::rf::ArmedState::ARMED;
            } else if (robot_arm_command.armed_state == fast::rf::ArmedState::ARMED) {
                armstate_change_request.requested_armed_state = fast::rf::ArmedState::DISARMED;
            }
        }
        auto mapped_joy = mapper.new_joy(joy);
        auto scaled_joy = scaler.new_joy(mapped_joy);
        auto new_twist = twist_computer.new_joy(scaled_joy);
        if (operation_mode == OperationMode::JOY_TEST) {
            std::string str = "Joy Test Mode";
            str += "\n\nInput:\n";
            str += joy.pretty();
            str += "\nMapped:\n\n";
            str += mapped_joy.pretty();
            str += "\nScaled:\n\n";
            str += scaled_joy.pretty();
            str += "\nTwist:\n\n";
            str += new_twist.pretty();

            fast::rf::Logger::log_debug(str);
        } else if (operation_mode == OperationMode::RUN) {
            desired_twist = new_twist;
        } else {
            fast::rf::Logger::log_error("Operation Mode: " + std::to_string((uint8_t)operation_mode) +
                                        " Not Supported.");
            return false;
        }

        return true;
    }

}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem