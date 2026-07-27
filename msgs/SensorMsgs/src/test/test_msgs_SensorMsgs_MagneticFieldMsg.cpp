
#include <gtest/gtest.h>
#include <stdio.h>

#include <MagneticFieldMsg.hpp>
using namespace fast::rf::messages::SensorMsgs;
TEST(MagneticFieldMsg, DefaultZeroConstructor) {
    MagneticFieldMsg SUT;
    ASSERT_GT(SUT.pretty().size(), 0);
}