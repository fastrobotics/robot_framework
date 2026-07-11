

#include <gtest/gtest.h>
#include <stdio.h>

#include <TankDriveExecutorProcess/TankDriveExecutorProcess.hpp>
#include <TwistMsg.hpp>
using namespace fast::rf::messages;
using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;

TEST(TankDriveExecutorProcess, SimpleTankConversionTests) {
    TankDriveExecutorProcess SUT;
    TankDriveChannelConfig left_channel_config(1000.0, 1500.0, 2000.0);
    TankDriveChannelConfig right_channel_config(1000.0, 1500.0, 2000.0);
    ASSERT_TRUE(SUT.set_config(left_channel_config, right_channel_config));
    if (1) {  // Neutral
        GeometryMsgs::TwistMsg twist;
        twist.linear.x = 0.0;
        twist.angular.z = 0.0;
        auto output = SUT.convert(twist);
        ASSERT_FLOAT_EQ(output.left_channel, 1500.0);
        ASSERT_FLOAT_EQ(output.right_channel, 1500.0);
    }
    if (1) {  // Full Forward
        GeometryMsgs::TwistMsg twist;
        twist.linear.x = 100.0;
        twist.angular.z = 0.0;
        auto output = SUT.convert(twist);
        ASSERT_FLOAT_EQ(output.left_channel, 2000.0);
        ASSERT_FLOAT_EQ(output.right_channel, 1000.0);
    }
    if (1) {  // Half Forward
        GeometryMsgs::TwistMsg twist;
        twist.linear.x = 50.0;
        twist.angular.z = 0.0;
        auto output = SUT.convert(twist);
        ASSERT_FLOAT_EQ(output.left_channel, 1750.0);
        ASSERT_FLOAT_EQ(output.right_channel, 1250.0);
    }
    if (1) {  // Full Backward
        GeometryMsgs::TwistMsg twist;
        twist.linear.x = -100.0;
        twist.angular.z = 0.0;
        auto output = SUT.convert(twist);
        ASSERT_FLOAT_EQ(output.left_channel, 1000.0);
        ASSERT_FLOAT_EQ(output.right_channel, 2000.0);
    }
    if (1) {  // Full Left
        GeometryMsgs::TwistMsg twist;
        twist.linear.x = 0.0;
        twist.angular.z = 100.0;
        auto output = SUT.convert(twist);
        ASSERT_FLOAT_EQ(output.left_channel, 1000.0);
        ASSERT_FLOAT_EQ(output.right_channel, 1000.0);
    }
    if (1) {  // Full Right
        GeometryMsgs::TwistMsg twist;
        twist.linear.x = 0.0;
        twist.angular.z = -100.0;
        auto output = SUT.convert(twist);
        ASSERT_FLOAT_EQ(output.left_channel, 2000.0);
        ASSERT_FLOAT_EQ(output.right_channel, 2000.0);
    }
}
TEST(TankDriveExecutorProcess, TestClipping) {
    TankDriveExecutorProcess SUT;
    TankDriveChannelConfig left_channel_config(1000.0, 1500.0, 2000.0);
    TankDriveChannelConfig right_channel_config(1000.0, 1500.0, 2000.0);
    ASSERT_TRUE(SUT.set_config(left_channel_config, right_channel_config));
    if (1) {  // Double Full Forward
        GeometryMsgs::TwistMsg twist;
        twist.linear.x = 200.0;
        twist.angular.z = 0.0;
        auto output = SUT.convert(twist);
        ASSERT_FLOAT_EQ(output.left_channel, 2000.0);
        ASSERT_FLOAT_EQ(output.right_channel, 1000.0);
    }
    if (1) {  // Double Full Backward
        GeometryMsgs::TwistMsg twist;
        twist.linear.x = -200.0;
        twist.angular.z = 0.0;
        auto output = SUT.convert(twist);
        ASSERT_FLOAT_EQ(output.left_channel, 1000.0);
        ASSERT_FLOAT_EQ(output.right_channel, 2000.0);
    }
    if (1) {  // Double Full Left
        GeometryMsgs::TwistMsg twist;
        twist.linear.x = 0.0;
        twist.angular.z = 200.0;
        auto output = SUT.convert(twist);
        ASSERT_FLOAT_EQ(output.left_channel, 1000.0);
        ASSERT_FLOAT_EQ(output.right_channel, 1000.0);
    }
    if (1) {  // Double Full Right
        GeometryMsgs::TwistMsg twist;
        twist.linear.x = 0.0;
        twist.angular.z = -200.0;
        auto output = SUT.convert(twist);
        ASSERT_FLOAT_EQ(output.left_channel, 2000.0);
        ASSERT_FLOAT_EQ(output.right_channel, 2000.0);
    }
}
struct TankDriveConversionTestData {
    double input_forward;   // [-100.0,100.0]
    double input_rotate;    // [-100.0,100.0]
    double expected_left;   // [1000.0,2000.0]
    double expected_right;  // [1000.0,2000.0]
    TankDriveConversionTestData(double input_forward, double input_rotate, double expected_left, double expected_right)
        : input_forward(input_forward),
          input_rotate(input_rotate),
          expected_left(expected_left),
          expected_right(expected_right){};
};

TEST(TankDriveExecutorProcess, ExtendedConversionTestCases) {
    // Build Test Cases
    std::vector<TankDriveConversionTestData> tests;
    {
        TankDriveConversionTestData test(0.0, 0.0, 1500.0, 1500.0);
        tests.push_back(test);
    }
    {
        TankDriveConversionTestData test(100.0, 0.0, 2000.0, 1000.0);
        tests.push_back(test);
    }
    {
        TankDriveConversionTestData test(-100.0, 0.0, 1000.0, 2000.0);
        tests.push_back(test);
    }
    {
        TankDriveConversionTestData test(0.0, 100.0, 1000.0, 1000.0);
        tests.push_back(test);
    }
    {
        TankDriveConversionTestData test(0.0, -100.0, 2000.0, 2000.0);
        tests.push_back(test);
    }
    {
        TankDriveConversionTestData test(50.0, 0.0, 1750.0, 1250.0);
        tests.push_back(test);
    }
    {
        TankDriveConversionTestData test(-50.0, 0.0, 1250.0, 1750.0);
        tests.push_back(test);
    }
    {
        TankDriveConversionTestData test(0.0, 50.0, 1250.0, 1250.0);
        tests.push_back(test);
    }
    {
        TankDriveConversionTestData test(0.0, -50.0, 1750.0, 1750.0);
        tests.push_back(test);
    }
    TankDriveExecutorProcess SUT;
    TankDriveChannelConfig left_channel_config(1000.0, 1500.0, 2000.0);
    TankDriveChannelConfig right_channel_config(1000.0, 1500.0, 2000.0);
    ASSERT_TRUE(SUT.set_config(left_channel_config, right_channel_config));
    for (auto test : tests) {
        GeometryMsgs::TwistMsg twist;
        twist.linear.x = test.input_forward;
        twist.angular.z = test.input_rotate;
        auto output = SUT.convert(twist);
        ASSERT_FLOAT_EQ(output.left_channel, test.expected_left);
        ASSERT_FLOAT_EQ(output.right_channel, test.expected_right);
    }
}