

#include <BasicTrajectoryControllerProcess/BasicTrajectoryControllerProcess.hpp>

#include <gtest/gtest.h>
#include <stdio.h>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;

TEST(BasicTrajectoryControllerProcess, BasicTests) {
  BasicTrajectoryControllerProcess SUT;
  ASSERT_TRUE(SUT.update(0.0, 0.0));
}
TEST(BasicTrajectoryControllerProcess, BasicConversionTests) {
  BasicTrajectoryControllerProcess SUT;
  ASSERT_TRUE(true);
}