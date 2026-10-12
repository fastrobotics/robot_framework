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
#include <PointCloudMsg.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    /**
     * @brief Removes noise from a Point Cloud
     *
     */
    class NoiseReducer {
       public:
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
        bool setConfig(double voxelSize_m, double radius_m, uint64_t minNeighborCount) {
            m_voxelSize_m = voxelSize_m;
            m_radius_m = radius_m;
            m_minNeighborCount = minNeighborCount;
            return true;
        }
        fast::rf::messages::SensorMsgs::PointCloudMsg reduceNoise(
            const fast::rf::messages::SensorMsgs::PointCloudMsg& overlapRemovedPointCloud);

       private:
        double m_voxelSize_m{0.035};
        double m_radius_m{0.05};
        uint64_t m_minNeighborCount{2};
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser