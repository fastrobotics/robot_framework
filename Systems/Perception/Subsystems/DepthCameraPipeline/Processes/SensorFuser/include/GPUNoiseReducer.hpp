#pragma once

#include <BaseNoiseReducer.hpp>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    class GPUNoiseReducer final : public BaseNoiseReducer {
       public:
        static bool isAvailable();

        bool init() override;

       protected:
        Cloud::Ptr filterCloud(const Cloud::ConstPtr& input) override;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
