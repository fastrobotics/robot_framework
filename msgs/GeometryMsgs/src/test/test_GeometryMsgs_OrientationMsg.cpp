
#include <gtest/gtest.h>
#include <stdio.h>

#include <OrientationMsg.hpp>
using namespace fast::rf::messages::GeometryMsgs;

TEST(OrientationMsg, DefaultZeroConstructor) {
    OrientationMsg SUT;
    ASSERT_FLOAT_EQ(SUT.roll, 0.0);
    ASSERT_FLOAT_EQ(SUT.pitch, 0.0);
    ASSERT_FLOAT_EQ(SUT.yaw, 0.0);
}