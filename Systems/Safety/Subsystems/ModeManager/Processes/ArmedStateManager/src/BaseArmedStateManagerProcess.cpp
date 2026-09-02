/**
 * @compare_tag Process-BaseSource v0.1
 *
 */
#include <BaseArmedStateManagerProcess.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager {
    bool BaseArmedStateManagerProcess::update(double currentTimeSec) {
        m_currentTimeSec = currentTimeSec;
        if (m_diagnosticManager.getDiagnostics(fast::rf::Level::ERROR).size() == 0) {
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
        str += "\tT: " + std::to_string(m_currentTimeSec) + "\n";

        str += m_diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager
