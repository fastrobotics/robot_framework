#pragma once

#include <INoiseReducer.hpp>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    bool isValidNoiseReducerConfig(const NoiseReducerConfig& config);

    class BaseNoiseReducer : public INoiseReducer {
       public:
        bool setConfig(const NoiseReducerConfig& config) override;
        bool init() override;
        fast::rf::messages::SensorMsgs::PointCloudMsg reduceNoise(
            const fast::rf::messages::SensorMsgs::PointCloudMsg& input) final;

       protected:
        using Cloud = pcl::PointCloud<pcl::PointXYZRGB>;
        NoiseReducerConfig m_config;

        virtual Cloud::Ptr filterCloud(const Cloud::ConstPtr& input) = 0;
        fast::rf::messages::SensorMsgs::PointCloudMsg emptyResult(double timestamp,
                                                                  const Cloud::ConstPtr& source = {}) const;
        Cloud::Ptr prepareCloud(const Cloud::ConstPtr& input) const;
        static fast::rf::messages::SensorMsgs::PointCloudMsg passthroughResult(
            const fast::rf::messages::SensorMsgs::PointCloudMsg& input);

       private:
        bool m_initialized{false};
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
