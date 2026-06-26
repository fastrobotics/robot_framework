

#include <BasicGlobalPoseProcess/BasicGlobalPoseProcess.hpp>

#include <gtest/gtest.h>
#include <stdio.h>

using namespace fast::rf::PoseSystem::GlobalPoseSubsystem;

TEST(BasicGlobalPoseProcess, BasicTests) {
  BasicGlobalPoseProcess SUT;
  SensorMsgs::GlobalPositionSensorData gps1;
  gps1.time_stamp = 0.3;
  ASSERT_FALSE(SUT.new_GlobalPositionSensorData(0, gps1));
  ASSERT_TRUE(SUT.update(0.0, 0.0));
  ASSERT_TRUE(SUT.new_GlobalPositionSensorData(0, gps1));
  GeometryMsgs::OdomMsg global_pose = SUT.get_GlobalPose();
  ASSERT_GT(global_pose.time_stamp, 0.0); // Valid Pose
}