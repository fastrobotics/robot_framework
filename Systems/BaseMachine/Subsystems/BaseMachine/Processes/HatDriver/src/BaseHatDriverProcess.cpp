#include <BaseHatDriverProcess.hpp>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem {
    bool BaseHatDriverProcess::update(double current_time_sec) {
        current_time_sec_ = current_time_sec;
        if (diagnosticManager.get_diagnostics(fast::rf::Level::WARN).size() == 0) {
            ready_to_arm.ready_to_arm = true;
        } else {
            ready_to_arm.ready_to_arm = false;
        }
        return true;
    }
    std::string BaseHatDriverProcess::pretty() {
        std::string str = "\n---HatDriver---\n";
        str += "\tT: " + std::to_string(current_time_sec_) + "\n";
        str += "\tReady To Arm: " + std::to_string(ready_to_arm.ready_to_arm) + "\n";
        str += diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem