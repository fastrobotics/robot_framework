
#include <gtest/gtest.h>
#include <stdio.h>

#include <PointMsg.hpp>
using namespace fast::rf::messages::GeometryMsgs;

TEST(PointMsg, DefaultZeroConstructor) {
    PointMsg SUT;
    ASSERT_FLOAT_EQ(SUT.x, 0.0);
    ASSERT_FLOAT_EQ(SUT.y, 0.0);
    ASSERT_FLOAT_EQ(SUT.z, 0.0);
}