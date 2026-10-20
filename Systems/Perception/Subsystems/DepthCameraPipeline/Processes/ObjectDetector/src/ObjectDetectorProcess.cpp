/**
 * @compare_tag Process-Source v0.1
 *
 */
#include <ObjectDetectorProcess.hpp>
#include <ObjectExtractor/ObjectExtractorCPU.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector {

    bool ObjectDetectorProcess::init() {
        bool status = BaseObjectDetectorProcess::init();
        if (status == false) {
            return false;
        }
        m_objectExtractor = std::make_unique<ObjectExtractorCPU>();
        if (m_objectExtractor->init() == false) {
            fast::rf::Logger::logError("Unable to initialize Object Extractor.");
            return false;
        }

        if (m_objectExtractor->setConfig(m_config.m_clusterToleranceDeg, m_config.m_minClusterSize) == false) {
            fast::rf::Logger::logError("Unable to set config for Object Extractor.");
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        m_diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::INFO,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "SW Running Ok.");
        return status;
    }
    bool ObjectDetectorProcess::update(double currentTimeSec) {
        bool status = BaseObjectDetectorProcess::update(currentTimeSec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::vector<fast::rf::messages::VisionMsgs::Detection3DMsg> ObjectDetectorProcess::detectObjects(
        fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud) {
        std::vector<fast::rf::messages::VisionMsgs::Detection3DMsg> detections;
        if (sensorCloud.size() > m_config.m_maxPointCloudSize) {
            m_diagnosticManager.updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE,
                                                 fast::rf::Level::WARN,
                                                 fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED,
                                                 "Point Cloud too large: " + std::to_string(sensorCloud.size()) +
                                                     " >= " + std::to_string(m_config.m_maxPointCloudSize));
            return detections;
        }
        detections = m_objectExtractor->extractObjects(sensorCloud);
        return detections;
    }
    std::string ObjectDetectorProcess::pretty() {
        std::string str = "--- ObjectDetector Process---";
        str += BaseObjectDetectorProcess::pretty();
        str += m_config.pretty();
        return str;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector
