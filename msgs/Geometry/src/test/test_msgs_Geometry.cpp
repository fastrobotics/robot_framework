
#include <GeometryMsg.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages::Standard;
using namespace fast::rf::messages::Geometry;

TEST(PointMsg, DefaultZeroConstructor) {
  PointMsg SUT;
  ASSERT_FLOAT_EQ(SUT.x, 0.0);
  ASSERT_FLOAT_EQ(SUT.y, 0.0);
  ASSERT_FLOAT_EQ(SUT.z, 0.0);
}
TEST(OrientationMsg, DefaultZeroConstructor) {
  OrientationMsg SUT;
  ASSERT_FLOAT_EQ(SUT.roll, 0.0);
  ASSERT_FLOAT_EQ(SUT.pitch, 0.0);
  ASSERT_FLOAT_EQ(SUT.yaw, 0.0);
}
TEST(PoseMsg, DefaultZeroConstructor) {
  PoseMsg SUT;
  // Nothing new to test
}
TEST(TwistMsg, DefaultZeroConstructor) {
  TwistMsg SUT;
  // Nothing new to test
}
TEST(PoseWithCovarianceMsg, DefaultZeroConstructor) {
  PoseWithCovarianceMsg SUT;
  ASSERT_LT(SUT.covariance.covariance[PoseWithCovarianceMsg::COV_X], 0.0);
  ASSERT_LT(SUT.covariance.covariance[PoseWithCovarianceMsg::COV_Y], 0.0);
  ASSERT_LT(SUT.covariance.covariance[PoseWithCovarianceMsg::COV_Z], 0.0);
  ASSERT_LT(SUT.covariance.covariance[PoseWithCovarianceMsg::COV_ROLL], 0.0);
  ASSERT_LT(SUT.covariance.covariance[PoseWithCovarianceMsg::COV_PITCH], 0.0);
  ASSERT_LT(SUT.covariance.covariance[PoseWithCovarianceMsg::COV_YAW], 0.0);
}
TEST(TwisthWithCovarianceMsg, DefaultZeroConstructor) {
  TwisthWithCovarianceMsg SUT;
  ASSERT_LT(SUT.covariance.covariance[TwisthWithCovarianceMsg::COV_LINEAR_X],
            0.0);
  ASSERT_LT(SUT.covariance.covariance[TwisthWithCovarianceMsg::COV_LINEAR_Y],
            0.0);
  ASSERT_LT(SUT.covariance.covariance[TwisthWithCovarianceMsg::COV_LINEAR_Z],
            0.0);
  ASSERT_LT(
      SUT.covariance.covariance[TwisthWithCovarianceMsg::COV_ANGULAR_ROLL],
      0.0);
  ASSERT_LT(
      SUT.covariance.covariance[TwisthWithCovarianceMsg::COV_ANGULAR_PITCH],
      0.0);
  ASSERT_LT(SUT.covariance.covariance[TwisthWithCovarianceMsg::COV_ANGULAR_YAW],
            0.0);
}
TEST(OdomMsg, DefaultZeroConstructor) {
  OdomMsg SUT;
  // Nothing new to test
}
/*
TEST(MsgPointWithCovariance, DefaultZeroConstructor) {
  PointWithCovarianceMsg SUT;
  ASSERT_EQ(SUT.covariance.covariance.size(),
            Covariance6DMsg::DIMENSION * Covariance6DMsg::DIMENSION);
}
TEST(MsgOrientation, DefaultZeroConstructor) {
  OrientationMsg SUT;
  ASSERT_FLOAT_EQ(SUT.roll, 0.0);
  ASSERT_FLOAT_EQ(SUT.pitch, 0.0);
  ASSERT_FLOAT_EQ(SUT.yaw, 0.0);
}
TEST(MsgOrientatioWithCovariance, DefaultZeroConstructor) {
  OrientationWithCovarianceMsg SUT;
  ASSERT_EQ(SUT.covariance.covariance.size(),
            Covariance6DMsg::DIMENSION * Covariance6DMsg::DIMENSION);
}
TEST(MsgPose, DefaultZeroConstructor) {
  PoseMsg SUT;
  ASSERT_FLOAT_EQ(SUT.time_stamp, 0.0);
}
*/