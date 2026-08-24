

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicTeleopControlProcess/BasicTeleopControlProcess.hpp>
#include <Infrastructure/Logger.hpp>
#include <cmath>

using namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem::TeleopControl;

TEST(BasicTeleopControlProcess, BasicTests) {
    BasicTeleopControlProcess SUT;
    JoystickCalibrationData joy_calibration;
    joy_calibration.optional_init();
    ASSERT_TRUE(SUT.init(ControlDevice::THRUSTMASTER_JOYSTICK, joy_calibration));
    ASSERT_TRUE(SUT.update(0.0));
    printf("%s\n", SUT.pretty().c_str());
}
TEST(BasicTeleopControlProcess, BasicConversionTests) {
    BasicTeleopControlProcess SUT;
    JoystickCalibrationData joy_calibration;
    joy_calibration.optional_init();
    ASSERT_TRUE(SUT.init(ControlDevice::THRUSTMASTER_JOYSTICK, joy_calibration));
}
TEST(BasicTeleopControlProcess, JoyTestMode) {
    BasicTeleopControlProcess SUT;
    JoystickCalibrationData joy_calibration;
    joy_calibration.optional_init();
    ASSERT_TRUE(SUT.init(ControlDevice::THRUSTMASTER_JOYSTICK, joy_calibration));
    ASSERT_TRUE(SUT.set_operation_mode(OperationMode::JOY_TEST));
    fast::rf::messages::SensorMsgs::JoyMsg joy;
    joy.buttons.resize(4);
    joy.axes.resize(3);
    EXPECT_TRUE(SUT.new_joy(joy));
    auto twist = SUT.get_twist_output();
    ASSERT_FLOAT_EQ(twist.linear.x, 0.0);
    ASSERT_FLOAT_EQ(twist.angular.z, 0.0);
}
TEST(BasicTeleopControlProcess, DefaultConfigJoystickInput) {
    BasicTeleopControlProcess SUT;
    fast::rf::messages::SensorMsgs::JoyMsg joy;
    joy.axes.resize(3);
    joy.buttons.resize(4);
    JoystickCalibrationData joy_calibration;
    joy_calibration.optional_init();
    ASSERT_TRUE(SUT.init(ControlDevice::THRUSTMASTER_JOYSTICK, joy_calibration));
    {  // Forward/Backwards Velocity

        ASSERT_TRUE(SUT.new_joy(joy));
        auto twist = SUT.get_twist_output();

        // Ensure we start at a forward stop

        ASSERT_FLOAT_EQ(twist.linear.x, 0.0);
        ASSERT_FLOAT_EQ(twist.angular.z, 0.0);
    }
}
TEST(BasicTeleopControlProcess, ConfigurationTests) {
    BasicTeleopControlProcess SUT;
    JoystickCalibrationData joy_calibration;
    joy_calibration.optional_init();
    EXPECT_TRUE(SUT.init(ControlDevice::THRUSTMASTER_JOYSTICK, joy_calibration));
    {                                                                // Forward Velocity Min/Max Configuration Checks
        ASSERT_FALSE(SUT.set_config(-100.0, 100.0, 100.0, -100.0));  // Max Reverse is higher than Max Forward
    }
    {                                                                // Angular Velocity Min/Max Configuration Checks
        ASSERT_FALSE(SUT.set_config(100.0, -100.0, -100.0, 100.0));  // Min Rate is higher than Max Rate
    }
    {  // Valid Configuration
        ASSERT_TRUE(SUT.set_config(100.0, -100.0, 100.0, -100.0));
    }
}
TEST(BasicTeleopControlProcess, TestInputTimeout) {
    BasicTeleopControlProcess SUT;
    JoystickCalibrationData joy_calibration;
    joy_calibration.optional_init();
    EXPECT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
    EXPECT_TRUE(SUT.init(ControlDevice::THRUSTMASTER_JOYSTICK, joy_calibration));
    double current_time = 0.0;
    EXPECT_TRUE(SUT.update(current_time));
    EXPECT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
    fast::rf::messages::SensorMsgs::JoyMsg joy;
    joy.buttons.resize(4);
    joy.buttons[0];
    EXPECT_TRUE(SUT.new_joy(joy));
    current_time += 0.1;
    EXPECT_TRUE(SUT.update(current_time));
    fast::rf::Logger::log_info(SUT.pretty());
    EXPECT_TRUE(SUT.get_ready_to_arm().ready_to_arm);

    current_time += 0.1 + ITeleopControlProcess::INPUT_TIMEOUT_SEC;
    EXPECT_TRUE(SUT.update(current_time));
    EXPECT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
    current_time += 0.1;
    EXPECT_TRUE(SUT.update(current_time));
    EXPECT_TRUE(SUT.new_joy(joy));
    current_time += 0.1;
    EXPECT_TRUE(SUT.update(current_time));
    EXPECT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
}
TEST(BasicTeleopControlProcess, ArmStateChangeRequest) {
    BasicTeleopControlProcess SUT;

    JoystickCalibrationData joy_calibration;
    joy_calibration.optional_init();
    EXPECT_TRUE(SUT.init(ControlDevice::THRUSTMASTER_JOYSTICK, joy_calibration));
    double current_time = 0.0;
    EXPECT_TRUE(SUT.update(current_time));
    fast::rf::messages::InfrastructureMsgs::ArmCommandMsg robot_arm_command;
    robot_arm_command.armed_state = fast::rf::ArmedState::DISARMED_CANNOTARM;
    fast::rf::messages::SensorMsgs::JoyMsg joy;
    joy.buttons.resize(4);
    joy.buttons[0];
    SUT.update_RobotArmCommand(robot_arm_command);
    EXPECT_TRUE(SUT.new_joy(joy));
    EXPECT_EQ(SUT.get_armstate_change_request().requested_armed_state, fast::rf::ArmedState::UNKNOWN);

    joy.buttons[1] = 1;
    joy.buttons[3] = 0;

    EXPECT_TRUE(SUT.new_joy(joy));
    EXPECT_EQ(SUT.get_armstate_change_request().requested_armed_state, fast::rf::ArmedState::UNKNOWN);

    robot_arm_command.armed_state = fast::rf::ArmedState::DISARMED;
    SUT.update_RobotArmCommand(robot_arm_command);
    EXPECT_TRUE(SUT.new_joy(joy));
    EXPECT_EQ(SUT.get_armstate_change_request().requested_armed_state, fast::rf::ArmedState::ARMED);
    EXPECT_EQ(SUT.get_armstate_change_request().requested_armed_state, fast::rf::ArmedState::UNKNOWN);

    robot_arm_command.armed_state = fast::rf::ArmedState::ARMED;
    SUT.update_RobotArmCommand(robot_arm_command);
    joy.buttons[1] = 0;
    joy.buttons[3] = 1;
    EXPECT_TRUE(SUT.new_joy(joy));
    EXPECT_EQ(SUT.get_armstate_change_request().requested_armed_state, fast::rf::ArmedState::DISARMED);
    EXPECT_EQ(SUT.get_armstate_change_request().requested_armed_state, fast::rf::ArmedState::UNKNOWN);

    robot_arm_command.armed_state = fast::rf::ArmedState::DISARMED;
    SUT.update_RobotArmCommand(robot_arm_command);
    joy.buttons[1] = 1;
    joy.buttons[3] = 0;
    EXPECT_TRUE(SUT.new_joy(joy));
    EXPECT_EQ(SUT.get_armstate_change_request().requested_armed_state, fast::rf::ArmedState::ARMED);
    EXPECT_EQ(SUT.get_armstate_change_request().requested_armed_state, fast::rf::ArmedState::UNKNOWN);
}