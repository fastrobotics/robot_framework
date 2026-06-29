

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicGlobalPoseProcess/BasicGlobalPoseProcess.hpp>

using namespace fast::rf::PoseSystem::GlobalPoseSubsystem;

TEST(BasicGlobalPoseProcess, BasicTests) {
    BasicGlobalPoseProcess SUT;
    SensorMsgs::GlobalPositionSensorMsg gps1;
    gps1.time_stamp = 0.3;
    ASSERT_TRUE(SUT.new_GlobalPositionSensorMsg(0, gps1));
    ASSERT_TRUE(SUT.update(0.0, 0.0));
    ASSERT_TRUE(SUT.new_GlobalPositionSensorMsg(0, gps1));
}
TEST(BasicGlobalPoseProcess, BasicConversionTests) {
    BasicGlobalPoseProcess SUT;
    SensorMsgs::GlobalPositionSensorMsg gps1;
    gps1.time_stamp = 1.0;
    gps1.latitude_deg = 40.7128;
    gps1.longitude_deg = -74.0060;
    gps1.covariance.covariance[SensorMsgs::GlobalPositionSensorMsg::COV_X] = 1.0;
    gps1.covariance.covariance[SensorMsgs::GlobalPositionSensorMsg::COV_Y] = 2.0;
    gps1.covariance.covariance[SensorMsgs::GlobalPositionSensorMsg::COV_Z] = 3.0;
    ASSERT_TRUE(SUT.new_GlobalPositionSensorMsg(0, gps1));
    GeometryMsgs::OdomMsg global_pose = SUT.get_GlobalPose();
    ASSERT_FLOAT_EQ(global_pose.pose.pose.position.x, 583959.372324);
    ASSERT_FLOAT_EQ(global_pose.pose.pose.position.y, 4507350.998243);
    ASSERT_FLOAT_EQ(global_pose.pose.covariance.covariance[GeometryMsgs::PoseWithCovarianceMsg::COV_X],
                    gps1.covariance.covariance[SensorMsgs::GlobalPositionSensorMsg::COV_X]);
    ASSERT_FLOAT_EQ(global_pose.pose.covariance.covariance[GeometryMsgs::PoseWithCovarianceMsg::COV_Y],
                    gps1.covariance.covariance[SensorMsgs::GlobalPositionSensorMsg::COV_Y]);
    ASSERT_FLOAT_EQ(global_pose.pose.covariance.covariance[GeometryMsgs::PoseWithCovarianceMsg::COV_Z],
                    gps1.covariance.covariance[SensorMsgs::GlobalPositionSensorMsg::COV_Z]);
    ASSERT_LT(global_pose.pose.covariance.covariance[GeometryMsgs::PoseWithCovarianceMsg::COV_ROLL], 0.0);
    ASSERT_LT(global_pose.pose.covariance.covariance[GeometryMsgs::PoseWithCovarianceMsg::COV_PITCH], 0.0);
    ASSERT_LT(global_pose.pose.covariance.covariance[GeometryMsgs::PoseWithCovarianceMsg::COV_YAW], 0.0);
}