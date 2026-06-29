
#include <gtest/gtest.h>
#include <stdio.h>

#include <Vector3DMsg.hpp>
using namespace fast::rf::messages::StandardMsgs;
TEST(Vector3DMsg, DefaultZeroConstructor) {
    Vector3DMsg SUT;
    ASSERT_FLOAT_EQ(SUT.x, 0.0);
    ASSERT_FLOAT_EQ(SUT.y, 0.0);
    ASSERT_FLOAT_EQ(SUT.z, 0.0);
}