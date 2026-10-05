#include <DepthCameraPipelineSubsystem.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem {
    bool DepthCameraPipelineSubsystem::init() { return false; }
    std::string DepthCameraPipelineSubsystem::pretty() {
        std::string str = "";
        return str;
    }
    bool DepthCameraPipelineSubsystem::newPointCloud([[maybe_unused]] fast::rf::messages::SensorMsgs::PointCloudMsg msg,
                                                     [[maybe_unused]] std::string sensorName) {
        return false;
    }
    bool DepthCameraPipelineSubsystem::update([[maybe_unused]] double currentTimeSec) { return false; }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem