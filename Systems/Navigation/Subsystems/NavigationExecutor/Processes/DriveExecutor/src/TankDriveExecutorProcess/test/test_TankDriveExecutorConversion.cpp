

#include <GeometryMsgs.hpp>
#include <TankDriveExecutorProcess/TankDriveExecutorProcess.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages;
using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;

TEST(TankDriveExecutorProcess, SimpleTankConversionTests) {
  TankDriveExecutorProcess SUT;
  TankDriveChannelConfig left_channel_config(1000.0, 1500.0, 2000.0);
  TankDriveChannelConfig right_channel_config(1000.0, 1500.0, 2000.0);
  SUT.set_config(left_channel_config, right_channel_config);
  { // Neutral
    GeometryMsgs::TwistMsg twist;
    twist.linear.x = 0.0;
    twist.angular.z = 0.0;
    auto output = SUT.convert(twist);
    ASSERT_FLOAT_EQ(output.left_channel, 1500.0);
    ASSERT_FLOAT_EQ(output.right_channel, 1500.0);
  }
  { // Full Forward
    GeometryMsgs::TwistMsg twist;
    twist.linear.x = 100.0;
    twist.angular.z = 0.0;
    auto output = SUT.convert(twist);
    ASSERT_FLOAT_EQ(output.left_channel, 2000.0);
    ASSERT_FLOAT_EQ(output.right_channel, 1000.0);
  }
  { // Full Backward
    GeometryMsgs::TwistMsg twist;
    twist.linear.x = -100.0;
    twist.angular.z = 0.0;
    auto output = SUT.convert(twist);
    ASSERT_FLOAT_EQ(output.left_channel, 1000.0);
    ASSERT_FLOAT_EQ(output.right_channel, 2000.0);
  }
  { // Full Left
    GeometryMsgs::TwistMsg twist;
    twist.linear.x = 0.0;
    twist.angular.z = 100.0;
    auto output = SUT.convert(twist);
    ASSERT_FLOAT_EQ(output.left_channel, 1000.0);
    ASSERT_FLOAT_EQ(output.right_channel, 1000.0);
  }
  { // Full Right
    GeometryMsgs::TwistMsg twist;
    twist.linear.x = 0.0;
    twist.angular.z = -100.0;
    auto output = SUT.convert(twist);
    ASSERT_FLOAT_EQ(output.left_channel, 2000.0);
    ASSERT_FLOAT_EQ(output.right_channel, 2000.0);
  }
}