

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicTrajectoryControllerProcess/BasicTrajectoryControllerProcess.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;

TEST(BasicTrajectoryControllerProcess, BasicTests) {
    BasicTrajectoryControllerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
    fast::rf::Logger::log_debug(SUT.pretty());
}
TEST(BasicTrajectoryControllerProcess, BasicInterfaceTests) {
    BasicTrajectoryControllerProcess SUT;
    ASSERT_TRUE(SUT.init());
}
TEST(BasicTrajectoryControllerProcess, ControllerTests) {
    BasicTrajectoryControllerProcess SUT;
    ASSERT_TRUE(false);
}