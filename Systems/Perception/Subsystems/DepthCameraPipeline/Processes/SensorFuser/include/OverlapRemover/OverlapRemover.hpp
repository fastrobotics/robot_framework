/**
 * @file OverlapRemover.hpp
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
     * @brief Removes overlap from combined Depth Camera Sensors
     *
     */
    class OverlapRemover {
       public:
        /**
         * @brief Initialize the object
         *
         * @return true
         * @return false
         */
        bool init();
        /**
         * @brief Remove overlap from the combined depth camera point cloud
         *
         * @param msg
         * @return fast::rf::messages::SensorMsgs::PointCloudMsg
         */
        fast::rf::messages::SensorMsgs::PointCloudMsg removeOverlap(fast::rf::messages::SensorMsgs::PointCloudMsg msg);

       private:
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser