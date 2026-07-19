#include <BaseTeleopControlProcess.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    bool BaseTeleopControlProcess::base_update(double current_time_sec) {
        current_time_sec_ = current_time_sec;

        return true;
    }
    std::string BaseTeleopControlProcess::pretty() {
        std::string str = "\n---Teleop Control---\n";
        if (operation_mode == OperationMode::RUN) {
            str += "\nOp Mode: RUN\n";
        } else if (operation_mode == OperationMode::JOY_TEST) {
            str += "\nOp Mode: JOY TEST\n";

        } else {
            str += "\nOp Mode: UNKNOWN\n";
        }
        str += "\tT: " + std::to_string(current_time_sec_) + "\n";
        str += "\tDesired Twist: " + desired_twist.pretty() + "\n";
        str += diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem