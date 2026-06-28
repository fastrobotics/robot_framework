

#include <BasicDriveExecutorProcess/BasicDriveExecutorProcess.hpp>

#include <gtest/gtest.h>
#include <stdio.h>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;

TEST(BasicDriveExecutorProcess, BasicTests) {
  BasicDriveExecutorProcess SUT;
  ASSERT_TRUE(SUT.update(0.0, 0.0));
}
TEST(BasicDriveExecutorProcess, BasicConversionTests) {
  BasicDriveExecutorProcess SUT;
  ASSERT_TRUE(true);
}