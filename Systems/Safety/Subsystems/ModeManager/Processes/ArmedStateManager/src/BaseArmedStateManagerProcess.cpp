#include <BaseArmedStateManagerProcess.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem {
    bool BaseArmedStateManagerProcess::update(double current_time_sec_) {
        current_time_sec = current_time_sec_;
        if (diagnosticManager.get_diagnostics(fast::rf::Level::ERROR).size() == 0) {
            ready_to_arm.ready_to_arm = true;
        } else {
            ready_to_arm.ready_to_arm = false;
        }
        return true;
    }
    std::string BaseArmedStateManagerProcess::pretty() {
        std::string str = "\n---ArmedStateManager---\n";
        str += "\tT: " + std::to_string(current_time_sec) + "\n";

        str += diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem