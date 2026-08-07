

#include <gtest/gtest.h>
#include <stdio.h>

#include <JoystickScaler.hpp>

using namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem;
TEST(JoystickScaler, InterfaceTestsThrustmasterJoystick) {
    JoystickScaler SUT;
    JoystickCalibrationData joy_calibration;
    joy_calibration.optional_init();
    EXPECT_TRUE(SUT.init(ControlDevice::THRUSTMASTER_JOYSTICK, joy_calibration));
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

    joy.axes[0] = -10.0;
    joy.axes[1] = 10.0;
    joy.axes[2] = -10.0;
    scaled_joy = SUT.new_joy(joy);
    ASSERT_EQ(scaled_joy.axes.size(), 3);

    ASSERT_FLOAT_EQ(scaled_joy.axes[0], -1.0 * JoystickScaler::AXIS_MAX_VALUE);
    ASSERT_FLOAT_EQ(scaled_joy.axes[1], JoystickScaler::AXIS_MAX_VALUE);
    ASSERT_FLOAT_EQ(scaled_joy.axes[2], -1.0 * JoystickScaler::AXIS_MAX_VALUE);
}
TEST(JoystickScaler, TestScaleFunction) {
    JoystickScaler SUT;
    ASSERT_FLOAT_EQ(SUT.scale_value(0.0, -1.0, 1.0, -1.0, 1.0), 0.0);
    ASSERT_FLOAT_EQ(SUT.scale_value(1.0, -1.0, 1.0, -1.0, 1.0), 1.0);
    ASSERT_FLOAT_EQ(SUT.scale_value(-1.0, -1.0, 1.0, -1.0, 1.0), -1.0);
    ASSERT_FLOAT_EQ(SUT.scale_value(0.5, -1.0, 1.0, -1.0, 1.0), 0.5);
    ASSERT_FLOAT_EQ(SUT.scale_value(-0.5, -1.0, 1.0, -1.0, 1.0), -0.5);
    ASSERT_FLOAT_EQ(SUT.scale_value(1, 0.0, 1.0, 0.0, 0.5), 0.5);
    ASSERT_FLOAT_EQ(SUT.scale_value(-1, -1.0, 0.0, -0.5, 0.0), -0.5);
}
TEST(JoystickScaler, TestCalibration) {
    JoystickScaler SUT;
    JoystickCalibrationData joy_calibration;
    joy_calibration.optional_init();
    joy_calibration.x_min = -0.5;
    joy_calibration.x_max = 0.5;
    joy_calibration.y_min = -0.5;
    joy_calibration.y_max = 0.5;
    joy_calibration.x_deadband = 0.1;
    joy_calibration.y_deadband = 0.1;
    EXPECT_TRUE(SUT.init(ControlDevice::THRUSTMASTER_JOYSTICK, joy_calibration));
    fast::rf::messages::SensorMsgs::JoyMsg joy;

    joy.axes.resize(3);
    joy.axes[2] = 0.0;
    {  // Test Center
        joy.axes[0] = 0.0;
        joy.axes[1] = 0.0;
        auto scaled_joy = SUT.new_joy(joy);
        ASSERT_EQ(scaled_joy.axes.size(), 3);

        ASSERT_FLOAT_EQ(scaled_joy.axes[0], 0.0);
        ASSERT_FLOAT_EQ(scaled_joy.axes[1], 0.0);
    }
    {  // Max Top Right Quadrant
        joy.axes[0] = 1.0;
        joy.axes[1] = 1.0;
        auto scaled_joy = SUT.new_joy(joy);
        ASSERT_EQ(scaled_joy.axes.size(), 3);

        ASSERT_FLOAT_EQ(scaled_joy.axes[0], joy_calibration.x_max);
        ASSERT_FLOAT_EQ(scaled_joy.axes[1], joy_calibration.y_max);
    }
    {  // Max Top Left Quadrant
        joy.axes[0] = -1.0;
        joy.axes[1] = 1.0;
        auto scaled_joy = SUT.new_joy(joy);
        ASSERT_EQ(scaled_joy.axes.size(), 3);

        ASSERT_FLOAT_EQ(scaled_joy.axes[0], joy_calibration.x_min);
        ASSERT_FLOAT_EQ(scaled_joy.axes[1], joy_calibration.y_max);
    }
    {  // Max Bottom Left Quadrant
        joy.axes[0] = -1.0;
        joy.axes[1] = -1.0;
        auto scaled_joy = SUT.new_joy(joy);
        ASSERT_EQ(scaled_joy.axes.size(), 3);

        ASSERT_FLOAT_EQ(scaled_joy.axes[0], joy_calibration.x_min);
        ASSERT_FLOAT_EQ(scaled_joy.axes[1], joy_calibration.y_min);
    }
    {  // Max Bottom Right Quadrant
        joy.axes[0] = 1.0;
        joy.axes[1] = -1.0;
        auto scaled_joy = SUT.new_joy(joy);
        ASSERT_EQ(scaled_joy.axes.size(), 3);

        ASSERT_FLOAT_EQ(scaled_joy.axes[0], joy_calibration.x_max);
        ASSERT_FLOAT_EQ(scaled_joy.axes[1], joy_calibration.y_min);
    }
}