

#include <GeometryMsgs.hpp>
#include <TankDriveExecutorProcess/TankDriveExecutorProcess.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages;
using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;

TEST(TankDriveExecutorProcess, AssertionTests) {
  TankDriveExecutorProcess SUT;
  ASSERT_TRUE(SUT.update(0.0, 0.0));
}
TEST(TankDriveExecutorProcess, TankConversionTests) {
  TankDriveExecutorProcess SUT;
  ASSERT_TRUE(true);
}
TEST(TankDriveExecutorProcess, UserInterfaceTests) {
  TankDriveExecutorProcess SUT;
  GeometryMsgs::TwistWithCovarianceMsg cmd;
  ASSERT_TRUE(false);
}