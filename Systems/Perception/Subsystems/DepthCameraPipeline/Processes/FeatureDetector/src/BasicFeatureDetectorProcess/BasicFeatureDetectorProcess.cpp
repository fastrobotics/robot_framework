/**
 * @compare_tag Process-BasicSource v0.1
 *
 */
#include <BasicFeatureDetectorProcess/BasicFeatureDetectorProcess.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector {

    bool BasicFeatureDetectorProcess::init() {
        bool status = BaseFeatureDetectorProcess::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    bool BasicFeatureDetectorProcess::update(double currentTimeSec) {
        bool status = BaseFeatureDetectorProcess::update(currentTimeSec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string BasicFeatureDetectorProcess::pretty() {
        std::string str = "---Basic FeatureDetector Process---";
        str += BaseFeatureDetectorProcess::pretty();
        return str;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector
