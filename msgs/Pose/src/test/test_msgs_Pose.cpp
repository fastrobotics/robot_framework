
#include <PoseMsg.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages::Pose;
TEST(MsgPoint, DefaultZeroConstructor) {
  PointMsg SUT;
  ASSERT_FLOAT_EQ(SUT.x, 0.0);
  ASSERT_FLOAT_EQ(SUT.y, 0.0);
  ASSERT_FLOAT_EQ(SUT.z, 0.0);
}
TEST(MsgPointWithCovariance, DefaultZeroConstructor) {
  PointWithCovarianceMsg SUT;
  ASSERT_EQ(SUT.covariance.covariance.size(), 36);
}
TEST(MsgOrientation, DefaultZeroConstructor) {
  OrientationMsg SUT;
  ASSERT_FLOAT_EQ(SUT.roll, 0.0);
  ASSERT_FLOAT_EQ(SUT.pitch, 0.0);
  ASSERT_FLOAT_EQ(SUT.yaw, 0.0);
}
TEST(MsgOrientatioWithCovariance, DefaultZeroConstructor) {
  OrientationWithCovarianceMsg SUT;
  ASSERT_EQ(SUT.covariance.covariance.size(), 36);
}
TEST(MsgPose, DefaultZeroConstructor) {
  PoseMsg SUT;
  ASSERT_FLOAT_EQ(SUT.time_stamp, 0.0);
}
