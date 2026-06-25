
#include <GeometryMsgs.hpp>

#include <IPoseSystem.hpp>

#include <BasePoseSystem.hpp>

#include <DummyPoseSystem/DummyPoseSystem.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages;
// Test message types typically owned by System
TEST(MsgPose, DefaultZeroConstructor) { GeometryMsgs::OdomMsg SUT; }

using namespace fast::rf::PoseSystem;
// System Interface Tests
class TestConcreteSystemInterface : public IPoseSystem {
public:
  bool update(double current_time_sec, double delta_time_sec) override {
    return false;
  }
  fast::rf::messages::GeometryMsgs::OdomMsg get_global_pose() {
    fast::rf::messages::GeometryMsgs::OdomMsg global_pose;
    return global_pose;
  }
  fast::rf::messages::GeometryMsgs::OdomMsg get_local_pose() {
    fast::rf::messages::GeometryMsgs::OdomMsg local_pose;
    return local_pose;
  }
};
TEST(PoseSystemInterface, BasicAssertionsInterface) {
  TestConcreteSystemInterface SUT;
  ASSERT_FALSE(SUT.update(0.0, 0.0));
  ASSERT_FLOAT_EQ(SUT.get_global_pose().pose.pose.position.x, 0.0);
}

// System Base Class Tests
class TestConcreteSystemBase : public BasePoseSystem {
public:
  bool update(double current_time_sec, double delta_time_sec) override {
    return base_update(current_time_sec, delta_time_sec);
  }
};
TEST(PoseSystemInterface, BasicAssertionsBaseClass) {
  TestConcreteSystemBase SUT;
  ASSERT_TRUE(SUT.update(0.0, 0.0));
}

// System Basic Class Tests