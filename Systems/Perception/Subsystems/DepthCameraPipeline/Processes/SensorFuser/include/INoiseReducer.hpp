#pragma once

#include <PointCloudMsg.hpp>
#include <cmath>
#include <cstdint>
#include <limits>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    struct NoiseReducerConfig {
        double voxelSize_m{0.035};
        double radius_m{0.05};
        uint64_t minNeighborCount{2};
    };

    inline bool isValidNoiseReducerConfig(const NoiseReducerConfig& config) {
        constexpr double max_float = std::numeric_limits<float>::max();
        if (!std::isfinite(config.voxelSize_m) || config.voxelSize_m <= 0.0 || config.voxelSize_m > max_float ||
            !std::isfinite(config.radius_m) || config.radius_m <= 0.0 || config.radius_m > max_float ||
            config.minNeighborCount >= static_cast<uint64_t>(std::numeric_limits<int>::max()))
            return false;

        const float voxel_size = static_cast<float>(config.voxelSize_m);
        const float radius = static_cast<float>(config.radius_m);
        const float radius_squared = radius * radius;
        return std::isfinite(voxel_size) && voxel_size > 0.0f && std::isfinite(radius) && radius > 0.0f &&
               std::isfinite(1.0f / radius) && radius_squared > 0.0f && std::isfinite(radius_squared);
    }

    class INoiseReducer {
       public:
        virtual ~INoiseReducer() = default;
        virtual bool init() = 0;
        virtual bool setConfig(const NoiseReducerConfig& config) = 0;
        virtual fast::rf::messages::SensorMsgs::PointCloudMsg reduceNoise(
            const fast::rf::messages::SensorMsgs::PointCloudMsg& input) = 0;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
