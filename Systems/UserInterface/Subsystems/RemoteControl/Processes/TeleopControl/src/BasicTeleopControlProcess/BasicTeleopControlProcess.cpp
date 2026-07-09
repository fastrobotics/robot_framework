#include <BasicTeleopControlProcess/BasicTeleopControlProcess.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {

    bool BasicTeleopControlProcess::init(ControlDevice device) {
        if ((device == ControlDevice::UNKNOWN) && (device == ControlDevice::END_OF_LIST)) {
            return false;
        }
        bool status = mapper.init(device);
        if (status == false) {
            return false;
        }
        status = scaler.init(device);
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL);
        status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool BasicTeleopControlProcess::update([[maybe_unused]] double current_time_sec,
                                           [[maybe_unused]] double delta_time_sec) {
        bool status = BaseTeleopControlProcess::base_update(current_time_sec, delta_time_sec);
        if (status == false) {
            return false;
        }
        return true;
    }
    bool BasicTeleopControlProcess::new_joy(fast::rf::messages::SensorMsgs::JoyMsg joy) {
        auto mapped_joy = mapper.new_joy(joy);
        auto scaled_joy = scaler.new_joy(mapped_joy);
        auto new_twist = twist_computer.new_joy(scaled_joy);
        if (operation_mode == OperationMode::JOY_TEST) {
            printf("Joy Test Mode\n");
            printf("\nInput\n");
            printf("%s\n", joy.pretty().c_str());
            printf("\nMapped\n");
            printf("%s\n", mapped_joy.pretty().c_str());
            printf("\nScaled\n");
            printf("%s\n", scaled_joy.pretty().c_str());
            printf("\nTwist:\n");
            printf("%s\n", new_twist.pretty().c_str());
        } else if (operation_mode == OperationMode::RUN) {
            desired_twist = new_twist;
        } else {
            return false;
        }

        return true;
    }

}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem