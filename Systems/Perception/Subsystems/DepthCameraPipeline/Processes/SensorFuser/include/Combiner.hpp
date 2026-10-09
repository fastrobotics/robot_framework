/**
 * @file Combiner.hpp
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
     * @brief Combines multiple Depth Camera Sensors into one
     *
     */
    class Combiner {
       public:
        /**
         * @brief Initialize the object
         *
         * @return true
         * @return false
         */
        bool init();
        /**
         * @brief Process a new Point Cloud
         *
         * @param msg
         * @param sensorIndex
         * @return true
         * @return false
         */
        bool newPointCloud(fast::rf::messages::SensorMsgs::PointCloudMsg msg, uint8_t sensorIndex);
        /**
         * @brief Check if a combined Point Cloud is available
         *
         * @return true
         * @return false
         */
        bool isCombinedPointCloudAvailable();
        /**
         * @brief Get the Combined Point Cloud object
         *
         * @return fast::rf::messages::SensorMsgs::PointCloudMsg
         */
        fast::rf::messages::SensorMsgs::PointCloudMsg getCombinedPointCloud();

       private:
        struct CombinerContainer {
            bool ready{false};
            fast::rf::messages::SensorMsgs::PointCloudMsg combinedPointCloud;
        };
        CombinerContainer m_combinedContainer;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser