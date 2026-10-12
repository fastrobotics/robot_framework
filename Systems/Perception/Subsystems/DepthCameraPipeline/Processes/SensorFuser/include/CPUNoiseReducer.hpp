#pragma once

#include <INoiseReducer.hpp>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    class CPUNoiseReducer final : public INoiseReducer {
       public:
        bool init() override;
        bool setConfig(const NoiseReducerConfig& config) override;
        fast::rf::messages::SensorMsgs::PointCloudMsg reduceNoise(
            const fast::rf::messages::SensorMsgs::PointCloudMsg& input) override;

       private:
        NoiseReducerConfig m_config;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
