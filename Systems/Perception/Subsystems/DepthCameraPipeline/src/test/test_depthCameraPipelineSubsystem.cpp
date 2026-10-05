#include <gtest/gtest.h>
#include <stdio.h>

#include <DepthCameraPipelineSubsystem.hpp>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem;
#include <Infrastructure/Logger.hpp>

TEST(DepthCameraPipelineSubsystem, BasicTests) {
    DepthCameraPipelineSubsystem SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);
    fast::rf::messages::SensorMsgs::PointCloudMsg pointCloud;
    ASSERT_TRUE(SUT.newPointCloud(pointCloud, "sensor1"));
    ASSERT_TRUE(SUT.update(0.0));
}