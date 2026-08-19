

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicTeleopControlProcess/TwistComputer.hpp>
#include <cmath>

using namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem::TeleopControl;

TEST(TwistComputer, BasicTwistComputeTests) {
    TwistComputer SUT;
    fast::rf::messages::SensorMsgs::JoyMsg joy;
    joy.axes.resize(3);
    joy.axes[0] = 100.0;
    joy.axes[1] = 100.0;
    auto twist = SUT.new_joy(joy);
    ASSERT_FLOAT_EQ(twist.linear.x, joy.axes[1]);
    ASSERT_FLOAT_EQ(twist.angular.z, joy.axes[0]);
}