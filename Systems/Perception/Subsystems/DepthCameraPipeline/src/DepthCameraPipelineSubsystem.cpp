#include <DepthCameraPipelineSubsystem.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem {
    bool DepthCameraPipelineSubsystem::init() {
        if (m_sensorHealthMonitorProcess->init() == false) {
            fast::rf::Logger::logError("Unable to initialize Sensor Health Monitor!");
            return false;
        }
        if (m_sensorInputHandlerProcess->init() == false) {
            fast::rf::Logger::logError("Unable to initialize Sensor Input Handler!");
            return false;
        }
        return true;
    }
    std::string DepthCameraPipelineSubsystem::pretty() {
        std::string str = "\n--- Depth Camera Pipeline Subsystem---\n";
        for (auto process : m_pipeline) {
            str += process.second->pretty();
        }
        return str;
    }
    bool DepthCameraPipelineSubsystem::newPointCloud(fast::rf::messages::SensorMsgs::PointCloudMsg msg,
                                                     std::string sensorName) {
        if (m_sensorHealthMonitorProcess.get()->newPointCloud(sensorName, msg) == false) {
            fast::rf::Logger::logWarn("Unable to process Sensor Point Cloud Signal: " + sensorName);
            return false;
        }
        auto convertedCloud = m_sensorInputHandlerProcess.get()->newPointCloud(msg);
        return true;
    }
    bool DepthCameraPipelineSubsystem::update([[maybe_unused]] double currentTimeSec) { return false; }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem