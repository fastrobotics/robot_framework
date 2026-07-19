#include <BaseTeleopControlProcess.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    bool BaseTeleopControlProcess::update(double current_time_sec) {
        current_time_sec_ = current_time_sec;
        if (diagnosticManager.get_diagnostics(fast::rf::Level::ERROR).size() == 0) {
            ready_to_arm.ready_to_arm = true;
        } else {
            ready_to_arm.ready_to_arm = false;
        }

        return true;
    }
    std::string BaseTeleopControlProcess::pretty() {
        std::string str = "";
        if (operation_mode == OperationMode::RUN) {
            str += "\nOp Mode: RUN\n";
        } else if (operation_mode == OperationMode::JOY_TEST) {
            str += "\nOp Mode: JOY TEST\n";

        } else {
            str += "\nOp Mode: UNKNOWN\n";
        }
        str += "\tT: " + std::to_string(current_time_sec_) + "\n";
        str += "\tReady To Arm: " + std::to_string(ready_to_arm.ready_to_arm) + "\n";
        str += "\tDesired Twist: " + desired_twist.pretty() + "\n";
        str += diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem