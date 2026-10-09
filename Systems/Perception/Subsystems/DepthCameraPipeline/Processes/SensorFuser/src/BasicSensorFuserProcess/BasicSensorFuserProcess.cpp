/**
 * @compare_tag Process-BasicSource v0.1
 *
 */
#include <BasicSensorFuserProcess/BasicSensorFuserProcess.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {

    bool BasicSensorFuserProcess::newPointCloud(fast::rf::messages::SensorMsgs::PointCloudMsg msg,
                                                uint8_t sensorIndex) {
        bool status = m_combiner.newPointCloud(msg, sensorIndex);
        return status;
    }
    bool BasicSensorFuserProcess::init() {
        if (BaseSensorFuserProcess::init() == false) {
            fast::rf::Logger::logError("Unable to initialize Base Process.");
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        if (m_diagnosticManager.initializeDiagnostics(diagnosticTypes) == false) {
            fast::rf::Logger::logError("Unable to initialize Diagnostic Manager.");
            return false;
        }
        if (m_combiner.init() == false) {
            fast::rf::Logger::logError("Unable to initialize Combiner.");
            return false;
        }
        return true;
    }
    bool BasicSensorFuserProcess::update(double currentTimeSec) {
        bool status = BaseSensorFuserProcess::update(currentTimeSec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string BasicSensorFuserProcess::pretty() {
        std::string str = "---Basic SensorFuser Process---";
        str += BaseSensorFuserProcess::pretty();
        return str;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
