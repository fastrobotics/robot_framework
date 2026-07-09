

#include <gtest/gtest.h>
#include <stdio.h>

#include <JoystickScaler.hpp>

using namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem;
TEST(JoystickScaler, InterfaceTestsThrustmasterJoystick) {
    JoystickScaler SUT;
    EXPECT_TRUE(SUT.init(ControlDevice::THRUSTMASTER_JOYSTICK));
    fast::rf::messages::SensorMsgs::JoyMsg joy;
    joy.axes.resize(3);
    joy.axes[0] = -1.0;
    joy.axes[1] = 1.0;
    joy.axes[2] = -1.0;
    auto scaled_joy = SUT.new_joy(joy);
    ASSERT_EQ(scaled_joy.axes.size(), 3);

    ASSERT_FLOAT_EQ(scaled_joy.axes[0], -1.0 * JoystickScaler::AXIS_MAX_VALUE);
    ASSERT_FLOAT_EQ(scaled_joy.axes[1], JoystickScaler::AXIS_MAX_VALUE);
    ASSERT_FLOAT_EQ(scaled_joy.axes[2], -1.0 * JoystickScaler::AXIS_MAX_VALUE);
}