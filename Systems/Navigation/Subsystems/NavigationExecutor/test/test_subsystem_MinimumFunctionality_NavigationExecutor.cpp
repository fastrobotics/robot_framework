
#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicTrajectoryControllerProcess/BasicTrajectoryControllerProcess.hpp>
#include <BasicTrajectorySelectorProcess/BasicTrajectorySelectorProcess.hpp>
#include <Infrastructure/Logger.hpp>
#include <TankDriveExecutorProcess/TankDriveExecutorProcess.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;
TEST(NavigationExecutorSubsystem, MinimumFunctionalityTests) {
    fast::rf::Logger::logNotice("Testing Navigation Executor Minimum Functionality.");

    TrajectorySelector::BasicTrajectorySelectorProcess selector;
    TrajectoryController::BasicTrajectoryControllerProcess controller;
    DriveExecutor::TankDriveExecutorProcess executor;
    // Initialization

    ASSERT_TRUE(selector.init());
    ASSERT_TRUE(controller.init());
    ASSERT_TRUE(executor.init());

    ASSERT_TRUE(selector.update(0.0));
    ASSERT_TRUE(controller.update(0.0));
    ASSERT_TRUE(executor.update(0.0));

    // Start a Control Cycle
    // Selector is not currently implemented/involved.

    fast::rf::messages::GeometryMsgs::OdomMsg pose;
    ASSERT_TRUE(controller.new_pose(pose));

    fast::rf::messages::GeometryMsgs::TwistMsg set_point_trajectory;
    ASSERT_TRUE(controller.new_desired_command(set_point_trajectory));

    fast::rf::messages::GeometryMsgs::TwistMsg execute_trajectory;
    ASSERT_TRUE(controller.get_command(execute_trajectory));

    auto drive_command = executor.new_cmd(execute_trajectory);
    ASSERT_NE(drive_command, nullptr);
}