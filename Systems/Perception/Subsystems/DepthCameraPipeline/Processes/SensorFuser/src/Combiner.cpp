#include <Combiner.hpp>
#include <Infrastructure/Logger.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    bool Combiner::init() { return true; }
    bool Combiner::newPointCloud(fast::rf::messages::SensorMsgs::PointCloudMsg msg, uint8_t sensorIndex) {
        if (sensorIndex > 0) {
            fast::rf::Logger::logWarn(
                "Only 1 Supported Depth Camera Sensor Currently.");  // Will resolve during AB#5755
            return false;
        }
        m_combinedContainer.combinedPointCloud = msg;
        m_combinedContainer.ready = true;
        return true;
    }
    bool Combiner::isCombinedPointCloudAvailable() { return m_combinedContainer.ready; }
    fast::rf::messages::SensorMsgs::PointCloudMsg Combiner::getCombinedPointCloud() {
        fast::rf::messages::SensorMsgs::PointCloudMsg cloud;
        if (m_combinedContainer.ready == true) {
            cloud = m_combinedContainer.combinedPointCloud;
            m_combinedContainer.ready = false;
        }
        return cloud;
    }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser