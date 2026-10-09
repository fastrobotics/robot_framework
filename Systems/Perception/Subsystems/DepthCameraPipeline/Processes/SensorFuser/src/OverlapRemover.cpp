#include <Infrastructure/Logger.hpp>
#include <OverlapRemover.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    bool OverlapRemover::init() { return true; }
    fast::rf::messages::SensorMsgs::PointCloudMsg OverlapRemover::removeOverlap(
        fast::rf::messages::SensorMsgs::PointCloudMsg msg) {
        return msg;
    }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser