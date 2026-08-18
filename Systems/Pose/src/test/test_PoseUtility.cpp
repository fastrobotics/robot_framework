
#include <gtest/gtest.h>

#include <PoseUtility.hpp>
using namespace fast::rf::PoseSystem;
TEST(PoseUtility, DifferentiatePose) {
    fast::rf::messages::GeometryMsgs::OdomMsg first_odom;
    first_odom.time_stamp = 0.0;
    first_odom.twist.twist.linear.x = 0.0;
    fast::rf::messages::GeometryMsgs::OdomMsg second_odom;
    second_odom.time_stamp = 1.0;
    second_odom.twist.twist.linear.x = 1.0;
    fast::rf::messages::GeometryMsgs::AccelMsg angular_acc;
    ASSERT_TRUE(PoseUtility::differentiate(first_odom, second_odom, angular_acc));
    ASSERT_FLOAT_EQ(angular_acc.linear.x, 1.0);
}