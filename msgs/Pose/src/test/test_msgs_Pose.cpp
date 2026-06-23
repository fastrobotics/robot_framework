
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
TEST(MsgPose, DefaultZeroConstructor) {
  PoseMsg SUT;
  ASSERT_FLOAT_EQ(SUT.point.x, 0.0);
}
