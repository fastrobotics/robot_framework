#pragma once

#include <INoiseReducer.hpp>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    class GPUNoiseReducer final : public INoiseReducer {
       public:
        static bool isAvailable();

        bool init() override;
        bool setConfig(const NoiseReducerConfig& config) override;
        fast::rf::messages::SensorMsgs::PointCloudMsg reduceNoise(
            const fast::rf::messages::SensorMsgs::PointCloudMsg& input) override;

       private:
        NoiseReducerConfig m_config;
        bool m_initialized{false};
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
