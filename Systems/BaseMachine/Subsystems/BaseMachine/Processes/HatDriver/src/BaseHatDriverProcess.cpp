/**
 * @compare_tag Process-BaseSource v0.1
 *
 */
#include <BaseHatDriverProcess.hpp>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver {
    bool BaseHatDriverProcess::update([[maybe_unused]] double currentTimeSec) {
        if (diagnosticManager.getDiagnostics(fast::rf::Level::WARN).size() == 0) {
            ready_to_arm.ready_to_arm = true;
        } else {
            ready_to_arm.ready_to_arm = false;
        }
        return true;
    }
    std::string BaseHatDriverProcess::pretty() {
        std::string str = "\n---HatDriver---\n";
        str += "\tSys: " + std::string(fast::rf::BaseMachineSystem::toString(fast::rf::BaseMachineSystem::Id{})) + "/" +
               std::string(fast::rf::BaseMachineSystem::BaseMachineSubsystem::toString(
                   fast::rf::BaseMachineSystem::BaseMachineSubsystem::Id{})) +
               "/" +
               std::string(fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver::toString(
                   fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver::Id{})) +
               "\n";
        str += "\tT: " + std::to_string(current_time_sec_) + "\n";
        str += "\tReady To Arm: " + std::to_string(ready_to_arm.ready_to_arm) + "\n";
        str += diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver
