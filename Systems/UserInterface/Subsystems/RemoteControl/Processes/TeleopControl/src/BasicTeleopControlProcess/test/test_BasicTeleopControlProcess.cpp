

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
    ASSERT_FALSE(SUT.key_pressed(KeyPressed::UNKNOWN));  // Unsupported Key
}
TEST(BasicTeleopControlProcess, BasicConversionTests) {
    BasicTeleopControlProcess SUT;
    ASSERT_TRUE(SUT.init());
}
TEST(BasicTeleopControlProcess, KeyTestMode) {
    BasicTeleopControlProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.set_operation_mode(OperationMode::KEY_TEST));
    auto twist = SUT.get_twist_output();
    ASSERT_FLOAT_EQ(twist.linear.x, 0.0);
    ASSERT_FLOAT_EQ(twist.angular.z, 0.0);

    for (uint16_t key = 0; key <= (uint8_t)KeyPressed::END_OF_LIST; ++key) {
        if ((key == 0) || (key == (uint8_t)KeyPressed::END_OF_LIST)) {  // Never Supported Keys
            ASSERT_FALSE(SUT.key_pressed((KeyPressed)key));
        } else if ((key == (uint8_t)KeyPressed::ESC)) {  // Not currently supported
            ASSERT_FALSE(SUT.key_pressed((KeyPressed)key));
        } else {
            printf("key: %d\n", key);
            ASSERT_TRUE(SUT.key_pressed((KeyPressed)key));
            twist = SUT.get_twist_output();
            ASSERT_FLOAT_EQ(twist.linear.x, 0.0);
            ASSERT_FLOAT_EQ(twist.angular.z, 0.0);
        }
    }
}
TEST(BasicTeleopControlProcess, DefaultConfigKeyPress) {
    BasicTeleopControlProcess SUT;
    ASSERT_TRUE(SUT.init());
    {  // Forward/Backwards Velocity

        ASSERT_TRUE(SUT.key_pressed(KeyPressed::SPACE_BAR));  // Command a Stop
        auto twist = SUT.get_twist_output();

        // Ensure we start at a forward stop

        ASSERT_FLOAT_EQ(twist.linear.x, 0.0);
        ASSERT_FLOAT_EQ(twist.angular.z, 0.0);

        // Command Forward Velocity Increase to Max
        uint16_t min_steps = (uint16_t)(SUT.MAX_VALUE / SUT.DEFAULT_STEP);
        for (uint16_t step = 0; step < (2 * min_steps);
             ++step) {  // Take care of any rounding issues, give it a lot of key presses
            ASSERT_TRUE(SUT.key_pressed(KeyPressed::UP_ARROW));
            twist = SUT.get_twist_output();
            ASSERT_GT(twist.linear.x, 0.0);                  // Should be positive
            ASSERT_LE(twist.linear.x, fabs(SUT.MAX_VALUE));  // Should always be less than or equal to the maximum value
        }
        // Should be at Max Forward Velocity
        twist = SUT.get_twist_output();
        ASSERT_FLOAT_EQ(twist.linear.x, fabs(SUT.MAX_VALUE));

        ASSERT_TRUE(SUT.key_pressed(KeyPressed::SPACE_BAR));  // Command a Stop
        twist = SUT.get_twist_output();

        // Ensure we start at a forward stop

        ASSERT_FLOAT_EQ(twist.linear.x, 0.0);
        ASSERT_FLOAT_EQ(twist.angular.z, 0.0);

        // Command Forward Velocity Increase to Max Reverse
        min_steps = (uint16_t)(SUT.MAX_VALUE / SUT.DEFAULT_STEP);
        for (uint16_t step = 0; step < (2 * min_steps);
             ++step) {  // Take care of any rounding issues, give it a lot of key presses
            ASSERT_TRUE(SUT.key_pressed(KeyPressed::DOWN_ARROW));
            twist = SUT.get_twist_output();
            ASSERT_LT(twist.linear.x, 0.0);  // Should be positive
            ASSERT_GE(twist.linear.x,
                      -1.0 * fabs(SUT.MAX_VALUE));  // Should always be greater than or equal to the minimum value
        }

        // Should be at Max Negative Forward Velocity
        twist = SUT.get_twist_output();
        ASSERT_FLOAT_EQ(twist.linear.x, -1.0 * fabs(SUT.MAX_VALUE));
    }
    {  // Left/Right Turn Velocity

        ASSERT_TRUE(SUT.key_pressed(KeyPressed::SPACE_BAR));  // Command a Stop
        auto twist = SUT.get_twist_output();

        // Ensure we start at a forward stop

        ASSERT_FLOAT_EQ(twist.linear.x, 0.0);
        ASSERT_FLOAT_EQ(twist.angular.z, 0.0);

        // Ensure we start at a forward stop
        ASSERT_FLOAT_EQ(twist.linear.x, 0.0);
        ASSERT_FLOAT_EQ(twist.angular.z, 0.0);

        // Command Left Turn Velocity Increase to Max
        uint16_t min_steps = (uint16_t)(SUT.MAX_VALUE / SUT.DEFAULT_STEP);
        for (uint16_t step = 0; step < (2 * min_steps);
             ++step) {  // Take care of any rounding issues, give it a lot of key presses
            ASSERT_TRUE(SUT.key_pressed(KeyPressed::LEFT_ARROW));
            twist = SUT.get_twist_output();
            ASSERT_GT(twist.angular.z, 0.0);  // Should be positive
            ASSERT_LE(twist.angular.z,
                      fabs(SUT.MAX_VALUE));  // Should always be less than or equal to the maximum value
        }
        // Should be at Max Forward Velocity
        twist = SUT.get_twist_output();
        ASSERT_FLOAT_EQ(twist.angular.z, fabs(SUT.MAX_VALUE));

        ASSERT_TRUE(SUT.key_pressed(KeyPressed::SPACE_BAR));  // Command a Stop
        twist = SUT.get_twist_output();

        // Ensure we start at a forward stop

        ASSERT_FLOAT_EQ(twist.linear.x, 0.0);
        ASSERT_FLOAT_EQ(twist.angular.z, 0.0);

        // Command Right Turn Velocity Increase to Max
        min_steps = (uint16_t)(SUT.MAX_VALUE / SUT.DEFAULT_STEP);
        for (uint16_t step = 0; step < (2 * min_steps);
             ++step) {  // Take care of any rounding issues, give it a lot of key presses
            ASSERT_TRUE(SUT.key_pressed(KeyPressed::RIGHT_ARROW));
            twist = SUT.get_twist_output();
            ASSERT_LT(twist.angular.z, 0.0);  // Should be positive
            ASSERT_GE(twist.angular.z,
                      -1.0 * fabs(SUT.MAX_VALUE));  // Should always be greater than or equal to the minimum value
        }

        // Should be at Max Negative Forward Velocity
        twist = SUT.get_twist_output();
        ASSERT_FLOAT_EQ(twist.angular.z, -1.0 * fabs(SUT.MAX_VALUE));
    }
}
TEST(BasicTeleopControlProcess, ConfigurationTests) {
    BasicTeleopControlProcess SUT;
    {  // Forward Velocity Min/Max Configuration Checks
        ASSERT_FALSE(
            SUT.set_config(10.0, 10.0, -100.0, 100.0, 100.0, -100.0));  // Max Reverse is higher than Max Forward
    }
    {
        // Forward Velocity Step Change Checks
        ASSERT_FALSE(SUT.set_config(1000.0, 10.0, 100.0, -100.0, 100.0, -100.0));
    }
    {  // Angular Velocity Min/Max Configuration Checks
        ASSERT_FALSE(SUT.set_config(10.0, 10.0, 100.0, -100.0, -100.0, 100.0));  // Min Rate is higher than Max Rate
    }
    {
        // Angular Velocity Step Change Checks
        ASSERT_FALSE(SUT.set_config(10.0, 1000.0, 100.0, -100.0, 100.0, -100.0));
    }
    {  // Valid Configuration
        ASSERT_TRUE(SUT.set_config(10.0, 10.0, 100.0, -100.0, 100.0, -100.0));
    }
}