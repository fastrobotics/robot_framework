#include <BaseArmedStateManagerProcess.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager {
    bool BaseArmedStateManagerProcess::update(double current_time_sec_) {
        current_time_sec = current_time_sec_;
        if (diagnosticManager.getDiagnostics(fast::rf::Level::ERROR).size() == 0) {
            /**
             * @todo Work on this during AB#1846.
             *
             */
            ready_to_arm.ready_to_arm = true;
        } else {
            ready_to_arm.ready_to_arm = false;
        }
        return true;
    }
    std::string BaseArmedStateManagerProcess::pretty() {
        std::string str = "\n---ArmedStateManager---\n";
        str += "\tSys: " + std::string(fast::rf::SafetySystem::toString(fast::rf::SafetySystem::Id{})) + "/" +
               std::string(fast::rf::SafetySystem::ModeManagerSubsystem::toString(
                   fast::rf::SafetySystem::ModeManagerSubsystem::Id{})) +
               "/" +
               std::string(fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager::toString(
                   fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager::Id{})) +
               "\n";
        str += "\tT: " + std::to_string(current_time_sec) + "\n";

        str += diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager