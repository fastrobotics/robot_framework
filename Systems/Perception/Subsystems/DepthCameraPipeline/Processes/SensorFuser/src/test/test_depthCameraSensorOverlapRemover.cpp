
#include <gtest/gtest.h>
#include <stdio.h>

#include <Infrastructure/Logger.hpp>
#include <OverlapRemover.hpp>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser;

TEST(DepthCameraOverlapRemover, BasicTests) {
    OverlapRemover SUT;
    ASSERT_TRUE(SUT.init());
    fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud;
    sensorCloud.time_stamp = 1.234;
    auto cloud = SUT.removeOverlap(sensorCloud);
    ASSERT_FLOAT_EQ(cloud.time_stamp, sensorCloud.time_stamp);
}
