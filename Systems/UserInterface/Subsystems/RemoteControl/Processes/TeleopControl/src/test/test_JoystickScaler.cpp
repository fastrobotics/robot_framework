

#include <gtest/gtest.h>
#include <stdio.h>

#include <JoystickScaler.hpp>

using namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem;
TEST(JoystickScaler, InterfaceTests) {
    JoystickScaler SUT;
    fast::rf::messages::SensorMsgs::JoyMsg joy;
    joy.axes.resize(3);
    auto scaled_joy = SUT.new_joy(joy);
    ASSERT_LT(scaled_joy.axes[0], 100.0);
}