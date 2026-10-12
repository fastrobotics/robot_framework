/**
 * @file NoiseReducer.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-08
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <INoiseReducer.hpp>
#include <memory>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    /**
     * @brief Removes noise from a Point Cloud
     *
     */
    class NoiseReducer {
       public:
        NoiseReducer() = default;
        ~NoiseReducer() = default;
        NoiseReducer(const NoiseReducer&) = delete;
        NoiseReducer& operator=(const NoiseReducer&) = delete;
        NoiseReducer(NoiseReducer&&) noexcept = default;
        NoiseReducer& operator=(NoiseReducer&&) noexcept = default;

        /**
         * @brief Initialize the object
         *
         * @return true
         * @return false
         */
        bool init();
        /**
         * @brief Set the Config object
         *
         * @param voxelSize_m Default=0.035 m How big of a voxel to Downsample
         * @param radius_m Default = 0.05
         * @param minNeighborCount Default = 2
         * @return true
         * @return false
         */
        bool setConfig(double voxelSize_m, double radius_m, uint64_t minNeighborCount);
        fast::rf::messages::SensorMsgs::PointCloudMsg reduceNoise(
            const fast::rf::messages::SensorMsgs::PointCloudMsg& overlapRemovedPointCloud);

       private:
        NoiseReducerConfig m_config;
        std::unique_ptr<INoiseReducer> m_backend;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser