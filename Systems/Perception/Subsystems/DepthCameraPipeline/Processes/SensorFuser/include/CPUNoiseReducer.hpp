#pragma once

#include <BaseNoiseReducer.hpp>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    class CPUNoiseReducer final : public BaseNoiseReducer {
       public:
       protected:
        Cloud::Ptr filterCloud(const Cloud::ConstPtr& input) override;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
