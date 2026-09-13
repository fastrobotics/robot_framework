/**
 * @compare_tag Process-BasicSource v0.1
 *
 */
#include <BasicExampleProcess/BasicExampleProcess.hpp>
namespace fast::rf::ExampleSystem::ExampleSubsystem::Example {

    bool BasicExampleProcess::init() {
        bool status = BaseExampleProcess::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    bool BasicExampleProcess::update(double currentTimeSec) {
        bool status = BaseExampleProcess::update(currentTimeSec);
        updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::INFO,
                         fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Software OK");
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string BasicExampleProcess::pretty() {
        std::string str = "---Basic Example Process---";
        str += BaseExampleProcess::pretty();
        return str;
    }

}  // namespace fast::rf::ExampleSystem::ExampleSubsystem::Example
