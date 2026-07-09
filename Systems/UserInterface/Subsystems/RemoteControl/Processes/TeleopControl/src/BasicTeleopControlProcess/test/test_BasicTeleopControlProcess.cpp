

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicTeleopControlProcess/BasicTeleopControlProcess.hpp>
#include <cmath>

using namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem;

TEST(BasicTeleopControlProcess, BasicTests) {
    BasicTeleopControlProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0, 0.0));
    printf("%s\n", SUT.pretty().c_str());
}
TEST(BasicTeleopControlProcess, BasicConversionTests) {
    BasicTeleopControlProcess SUT;
    ASSERT_TRUE(SUT.init());
}
TEST(BasicTeleopControlProcess, JoyTestMode) {
    BasicTeleopControlProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.set_operation_mode(OperationMode::JOY_TEST));
    auto twist = SUT.get_twist_output();
    ASSERT_FLOAT_EQ(twist.linear.x, 0.0);
    ASSERT_FLOAT_EQ(twist.angular.z, 0.0);
}
TEST(BasicTeleopControlProcess, DefaultConfigJoystickInput) {
    BasicTeleopControlProcess SUT;
    fast::rf::messages::SensorMsgs::JoyMsg joy;

    ASSERT_TRUE(SUT.init());
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