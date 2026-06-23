
#include <PoseMsg.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::fr::messages;
TEST(MsgPose, DefaultZeroConstructor) {
  Pose::PoseMsg SUT;
  ASSERT_TRUE(false);
}