/**
 * @compare_tag Process-BasicSource v0.1
 *
 */
#include <BasicFeatureDetectorProcess/BasicFeatureDetectorProcess.hpp>
#include <FeatureExtractor/FeatureExtractorCPU.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector {

    bool BasicFeatureDetectorProcess::init() {
        bool status = BaseFeatureDetectorProcess::init();
        if (status == false) {
            return false;
        }
        m_featureExtractor = std::make_unique<FeatureExtractorCPU>();
        if (m_featureExtractor->init() == false) {
            fast::rf::Logger::logError("Unable to initialize Feature Extractor.");
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    bool BasicFeatureDetectorProcess::update(double currentTimeSec) {
        bool status = BaseFeatureDetectorProcess::update(currentTimeSec);
        if (status == false) {
            return false;
        }
        if (m_featureExtractor->update(currentTimeSec) == false) {
            fast::rf::Logger::logWarn("Unable to update Feature Extractor.");
        }
        return true;
    }
    std::string BasicFeatureDetectorProcess::pretty() {
        std::string str = "---Basic FeatureDetector Process---";
        str += BaseFeatureDetectorProcess::pretty();
        str += m_featureExtractor->pretty();
        return str;
    }
    fast::rf::messages::SensorMsgs::PointCloudMsg BasicFeatureDetectorProcess::detectFeatures(
        fast::rf::messages::SensorMsgs::PointCloudMsg pointCloud) {
        auto featurePointCloudContainer = m_featureExtractor->extractFeatures(pointCloud);
        if (featurePointCloudContainer.wereFeaturesExtracted) {
            m_featurePointCloudReady = true;
            m_diagnosticManager.updateDiagnostic(
                fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::INFO,
                fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Extracting Features Ok.");
        }
        return featurePointCloudContainer.cloud;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector
