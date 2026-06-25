
#include <GeometryMsgs.hpp>

#include <DummyPoseSystem/DummyPoseSystem.hpp>

#include <gtest/gtest.h>
using namespace fast::rf::PoseSystem;
TEST(DummyPoseSyste, BasicAssertions) {
  DummyPoseSystem SUT;
  ASSERT_TRUE(SUT.update(0.0, 0.0));
  ASSERT_FLOAT_EQ(SUT.get_global_pose().time_stamp, 0.0);
  ASSERT_FLOAT_EQ(SUT.get_local_pose().time_stamp, 0.0);
  ASSERT_TRUE(SUT.update(1.0, 0.0));
  ASSERT_FLOAT_EQ(SUT.get_global_pose().time_stamp, 1.0);
  ASSERT_FLOAT_EQ(SUT.get_local_pose().time_stamp, 1.0);
}