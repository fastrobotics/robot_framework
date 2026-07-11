#include <BaseHatDriverProcess.hpp>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem {
    bool BaseHatDriverProcess::base_update([[maybe_unused]] double current_time_sec,
                                           [[maybe_unused]] double delta_time_sec) {
        current_time_sec_ = current_time_sec;

        return true;
    }
    std::string BaseHatDriverProcess::pretty() {
        std::string str = "\n---HatDriver---\n";
        str += "\tT: " + std::to_string(current_time_sec_) + "\n";

        str += diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem