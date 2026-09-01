/**
 * @compare_tag Process-BasicSourceTest v0.1
 *
 */
#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicTrajectoryControllerProcess/BasicTrajectoryControllerProcess.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController;

TEST(BasicTrajectoryControllerProcess, BasicTests) {
    BasicTrajectoryControllerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
    fast::rf::Logger::logDebug(SUT.pretty());
}
TEST(BasicTrajectoryControllerProcess, BasicInterfaceTests) {
    BasicTrajectoryControllerProcess SUT;
    ASSERT_TRUE(SUT.init());

    fast::rf::NavigationSystem::Controller::PIDControllerConfig pid_config;
    pid_config.set_parameters(5.0, -5.0, 2.0, 2.0, 0.0, 0.0);
    BasicTrajectoryControllerConfig config;
    ASSERT_TRUE(config.set_pid_controller_config(pid_config));
    ASSERT_TRUE(SUT.set_config(config));
    ASSERT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
    fast::rf::messages::GeometryMsgs::TwistMsg desired_command;
    desired_command.linear.x = 1.0;
    desired_command.angular.z = 1.0;
    ASSERT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
    ASSERT_TRUE(SUT.new_desired_command(desired_command));
    fast::rf::messages::GeometryMsgs::OdomMsg pose;
    ASSERT_TRUE(SUT.new_pose(pose));
    ASSERT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
    ASSERT_TRUE(SUT.update(0.0));
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
    fast::rf::Logger::logDebug(SUT.pretty());
    fast::rf::messages::GeometryMsgs::TwistMsg command;
    ASSERT_TRUE(SUT.get_command(command));
    ASSERT_FLOAT_EQ(command.linear.x, desired_command.linear.x);
    ASSERT_NE(command.angular.z, 0.0);
    ASSERT_NE(command.angular.z, desired_command.angular.z);
}
