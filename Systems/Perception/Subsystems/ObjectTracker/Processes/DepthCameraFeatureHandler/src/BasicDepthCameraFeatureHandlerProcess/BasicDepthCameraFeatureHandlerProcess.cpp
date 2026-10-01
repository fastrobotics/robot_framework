/**
 * @compare_tag Process-BasicSource v0.1
 *
 */
#include <BasicDepthCameraFeatureHandlerProcess/BasicDepthCameraFeatureHandlerProcess.hpp>
namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::DepthCameraFeatureHandler {

    bool BasicDepthCameraFeatureHandlerProcess::init() {
        bool status = BaseDepthCameraFeatureHandlerProcess::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    bool BasicDepthCameraFeatureHandlerProcess::update(double currentTimeSec) {
        bool status = BaseDepthCameraFeatureHandlerProcess::update(currentTimeSec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string BasicDepthCameraFeatureHandlerProcess::pretty() {
        std::string str = "---Basic DepthCameraFeatureHandler Process---";
        str += BaseDepthCameraFeatureHandlerProcess::pretty();
        return str;
    }

}  // namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::DepthCameraFeatureHandler
