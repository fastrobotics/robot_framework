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
#include <PointCloudTools.hpp>
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
        fast::rf::messages::SensorMsgs::PointCloudMsg reduceNoise(
            fast::rf::messages::SensorMsgs::PointCloudMsg overlapRemovedPointCloud);

       private:
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser