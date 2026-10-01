/**
 * @compare_tag Process-BasicSource v0.1
 *
 */
#include <BasicObjectManagerProcess/BasicObjectManagerProcess.hpp>
namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::ObjectManager {

    bool BasicObjectManagerProcess::init() {
        bool status = BaseObjectManagerProcess::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    bool BasicObjectManagerProcess::update(double currentTimeSec) {
        bool status = BaseObjectManagerProcess::update(currentTimeSec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string BasicObjectManagerProcess::pretty() {
        std::string str = "---Basic ObjectManager Process---";
        str += BaseObjectManagerProcess::pretty();
        return str;
    }

}  // namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::ObjectManager
