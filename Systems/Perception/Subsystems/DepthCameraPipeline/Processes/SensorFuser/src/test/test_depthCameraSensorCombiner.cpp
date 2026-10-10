
#include <gtest/gtest.h>
#include <stdio.h>

#include <Combiner.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser;

TEST(DepthCameraSensorCombiner, BasicTests) {
    Combiner SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_FALSE(SUT.isCombinedPointCloudAvailable());
    fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud;
    sensorCloud.time_stamp = 1.234;
    EXPECT_TRUE(SUT.newPointCloud(sensorCloud, 0));
    EXPECT_TRUE(SUT.isCombinedPointCloudAvailable());
    auto cloud = SUT.getCombinedPointCloud();
    ASSERT_FLOAT_EQ(cloud.time_stamp, sensorCloud.time_stamp);
    ASSERT_FALSE(SUT.isCombinedPointCloudAvailable());
    auto badCloud = SUT.getCombinedPointCloud();
    ASSERT_LT(badCloud.time_stamp, 0.0);
    ASSERT_EQ(badCloud.point_cloud->height, 0);
    ASSERT_EQ(badCloud.point_cloud->width, 0);
}
TEST(DepthCameraSensorCombiner, FailureTests) {
    Combiner SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_FALSE(SUT.isCombinedPointCloudAvailable());
    fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud;
    sensorCloud.time_stamp = 1.234;
    EXPECT_FALSE(
        SUT.newPointCloud(sensorCloud, 1));  // Only 1 Supported Depth Camera Sensor.  More added during AB#5755
}