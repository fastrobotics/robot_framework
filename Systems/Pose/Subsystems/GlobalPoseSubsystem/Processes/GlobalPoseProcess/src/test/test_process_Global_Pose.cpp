
#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseGlobalPoseProcess.hpp>
#include <GlobalPositionSensorMsg.hpp>
#include <IGlobalPoseProcess.hpp>

using namespace fast::rf::PoseSystem::GlobalPoseSubsystem;
class TestGlobalPoseProcessInterface : public IGlobalPoseProcess {
   public:
    uint8_t get_supported_gps_channel_count() { return 0; }
    bool update(double current_time_sec, double delta_time_sec) override { return false; }
    bool new_GlobalPositionSensorMsg(uint8_t index, SensorMsgs::GlobalPositionSensorMsg data) override { return false; }
    GeometryMsgs::OdomMsg get_GlobalPose() override {
        GeometryMsgs::OdomMsg global_pose;
        return global_pose;
    }
};
TEST(TestGlobalPoseProcessInterface, InterfaceTests) {
    TestGlobalPoseProcessInterface SUT;
    SensorMsgs::GlobalPositionSensorMsg gps1;
    ASSERT_FALSE(SUT.new_GlobalPositionSensorMsg(0, gps1));
    ASSERT_FALSE(SUT.update(0.0, 0.0));
    GeometryMsgs::OdomMsg global_pose = SUT.get_GlobalPose();
    ASSERT_LT(global_pose.time_stamp, 0.0);  // Invalid Pose
}
class TestBaseGlobalPoseProcess : public BaseGlobalPoseProcess {
   public:
    TestBaseGlobalPoseProcess() : BaseGlobalPoseProcess(0) {}

    bool update(double current_time_sec, double delta_time_sec) override {
        return base_update(current_time_sec, delta_time_sec);
    }
    bool new_GlobalPositionSensorMsg(uint8_t index, SensorMsgs::GlobalPositionSensorMsg data) override {
        if (current_time_sec_ < 0) {
            return false;
        }
        global_pose.time_stamp = data.time_stamp;
        return true;
    }
};
TEST(BaseGlobalPoseProcess, BasicAssertions) {
    TestBaseGlobalPoseProcess SUT;
    SensorMsgs::GlobalPositionSensorMsg gps1;
    gps1.time_stamp = 0.3;
    ASSERT_FALSE(SUT.new_GlobalPositionSensorMsg(0, gps1));
    ASSERT_TRUE(SUT.update(0.0, 0.0));
    ASSERT_TRUE(SUT.new_GlobalPositionSensorMsg(0, gps1));
    GeometryMsgs::OdomMsg global_pose = SUT.get_GlobalPose();
    ASSERT_GT(global_pose.time_stamp, 0.0);  // Valid Pose
}