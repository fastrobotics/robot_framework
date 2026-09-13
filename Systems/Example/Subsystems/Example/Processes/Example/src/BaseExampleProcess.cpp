/**
 * @compare_tag Process-BaseSource v0.1
 *
 */
#include <BaseExampleProcess.hpp>
namespace fast::rf::ExampleSystem::ExampleSubsystem::Example {
    bool BaseExampleProcess::init() { return true; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> BaseExampleProcess::getDiagnostics() {
        return m_diagnosticManager.getDiagnostics();
    }
    bool BaseExampleProcess::update(double currentTimeSec) {
        m_currentTimeSec = currentTimeSec;
        if (m_diagnosticManager.getDiagnostics(fast::rf::Level::ERROR).size() == 0) {
            m_readyToArm.ready_to_arm = true;
        } else {
            m_readyToArm.ready_to_arm = false;
        }

        return true;
    }
    bool BaseExampleProcess::initializeDiagnostics(
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes) {
        bool status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    std::string BaseExampleProcess::pretty() {
        std::string str = "\n---Example---\n";
        str += "\tSys: " + std::string(fast::rf::ExampleSystem::toString(fast::rf::ExampleSystem::Id{})) + "/" +
               std::string(fast::rf::ExampleSystem::ExampleSubsystem::toString(
                   fast::rf::ExampleSystem::ExampleSubsystem::Id{})) +
               "/" +
               std::string(fast::rf::ExampleSystem::ExampleSubsystem::Example::toString(
                   fast::rf::ExampleSystem::ExampleSubsystem::Example::Id{})) +
               "\n";
        str += "\tT: " + std::to_string(m_currentTimeSec) + "\n";
        str += "\tReady To Arm: " + std::to_string(m_readyToArm.ready_to_arm) + "\n";
        str += m_diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::ExampleSystem::ExampleSubsystem::Example
