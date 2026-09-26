/**
 * @compare_tag Process-BasicSource v0.1
 *
 */
#include <BasicFOVExtractorProcess/BasicFOVExtractorProcess.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FOVExtractor {

    bool BasicFOVExtractorProcess::init() {
        bool status = BaseFOVExtractorProcess::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    bool BasicFOVExtractorProcess::update(double currentTimeSec) {
        bool status = BaseFOVExtractorProcess::update(currentTimeSec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string BasicFOVExtractorProcess::pretty() {
        std::string str = "---Basic FOVExtractor Process---";
        str += BaseFOVExtractorProcess::pretty();
        return str;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FOVExtractor
