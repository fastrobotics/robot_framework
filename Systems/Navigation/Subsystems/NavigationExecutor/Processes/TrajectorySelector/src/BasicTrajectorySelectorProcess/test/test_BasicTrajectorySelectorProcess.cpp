

#include <BasicTrajectorySelectorProcess/BasicTrajectorySelectorProcess.hpp>

#include <gtest/gtest.h>
#include <stdio.h>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;

TEST(BasicTrajectorySelectorProcess, BasicTests) {
  BasicTrajectorySelectorProcess SUT;
  ASSERT_TRUE(SUT.update(0.0, 0.0));
}
TEST(BasicTrajectorySelectorProcess, BasicConversionTests) {
  BasicTrajectorySelectorProcess SUT;
  ASSERT_TRUE(true);
}