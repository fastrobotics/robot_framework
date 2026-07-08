#include <BaseTeleopControlProcess.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    bool BaseTeleopControlProcess::base_update([[maybe_unused]] double current_time_sec,
                                               [[maybe_unused]] double delta_time_sec) {
        current_time_sec_ = current_time_sec;

        return true;
    }
    std::string BaseTeleopControlProcess::pretty() {
        std::string str = "\n---Teleop Control---\n";
        str += "\tT: " + std::to_string(current_time_sec_) + "\n";

        str += diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem