/**
 * @compare_tag Process-BasicSource v0.1
 *
 */
#include <BasicObjectEstimatorProcess/BasicObjectEstimatorProcess.hpp>
namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::ObjectEstimator {

    bool BasicObjectEstimatorProcess::init() {
        bool status = BaseObjectEstimatorProcess::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    bool BasicObjectEstimatorProcess::update(double currentTimeSec) {
        bool status = BaseObjectEstimatorProcess::update(currentTimeSec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string BasicObjectEstimatorProcess::pretty() {
        std::string str = "---Basic ObjectEstimator Process---";
        str += BaseObjectEstimatorProcess::pretty();
        return str;
    }

}  // namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::ObjectEstimator
