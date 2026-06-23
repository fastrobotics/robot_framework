
#include <PoseMsg.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::fr::messages;
TEST(MsgPose, DefaultZeroConstructor) {
  PoseMsg SUT;
  ASSERT_FLOAT_EQ(SUT.x, 0.0);
  ASSERT_FLOAT_EQ(SUT.y, 0.0);
  ASSERT_FLOAT_EQ(SUT.z, 0.0);
}
TEST(MsgPose, DefaultConfigConstructor) {
  PoseMsg SUT(1.0, 2.0, 3.0);
  ASSERT_FLOAT_EQ(SUT.x, 1.0);
  ASSERT_FLOAT_EQ(SUT.y, 2.0);
  ASSERT_FLOAT_EQ(SUT.z, 3.0);
}