#pragma once

#include <PointCloudMsg.hpp>
#include <cstdint>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    struct NoiseReducerConfig {
        double voxelSize_m{0.035};
        double radius_m{0.1};
        uint64_t minNeighborCount{3};
    };

    class INoiseReducer {
       public:
        virtual ~INoiseReducer() = default;
        virtual bool setConfig(const NoiseReducerConfig& config) = 0;
        virtual bool init() = 0;
        virtual fast::rf::messages::SensorMsgs::PointCloudMsg reduceNoise(
            const fast::rf::messages::SensorMsgs::PointCloudMsg& input) = 0;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
