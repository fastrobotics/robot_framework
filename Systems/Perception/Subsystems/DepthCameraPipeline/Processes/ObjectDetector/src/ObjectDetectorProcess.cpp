/**
 * @compare_tag Process-Source v0.1
 *
 */
#include <ObjectDetectorProcess.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector {

    bool ObjectDetectorProcess::init() {
        bool status = BaseObjectDetectorProcess::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    bool ObjectDetectorProcess::update(double currentTimeSec) {
        bool status = BaseObjectDetectorProcess::update(currentTimeSec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string ObjectDetectorProcess::pretty() {
        std::string str = "--- ObjectDetector Process---";
        str += BaseObjectDetectorProcess::pretty();
        return str;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector
