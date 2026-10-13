
#include <gtest/gtest.h>
#include <stdio.h>

#include <PointCloudMsg.hpp>
using namespace fast::rf::messages::SensorMsgs;
TEST(PointCloudMsg, DefaultZeroConstructor) {
    PointCloudMsg SUT;
    ASSERT_LT(SUT.time_stamp, 0);
}
TEST(PointCloudMsg, PrettyFunctions) {
    PointCloudMsg SUT;
    SUT.point_cloud->points.resize(2);
    EXPECT_EQ(SUT.size(), 2);
    EXPECT_FALSE(SUT.empty());
    ASSERT_GT(SUT.pretty().size(), 0);
}
TEST(PointCloudMsg, HelperFunctions) {
    PointCloudMsg pointCloud = PointCloudMsg::generateRGBCloud(4);
    EXPECT_FALSE(pointCloud.empty());
    EXPECT_EQ(pointCloud.size(), 64);
    ASSERT_EQ(pointCloud.point_cloud->width, 4);
    ASSERT_EQ(pointCloud.point_cloud->height, 16);
    ASSERT_EQ(pointCloud.point_cloud->size(), 64);
    ASSERT_EQ(pointCloud.point_cloud->points[0].r, 0);
    ASSERT_EQ(pointCloud.point_cloud->points.back().b, 255);
}