
#include <gtest/gtest.h>
#include <stdio.h>

#include <JoyMsg.hpp>
using namespace fast::rf::messages::SensorMsgs;
TEST(JoyMsg, DefaultZeroConstructor) {
    JoyMsg SUT;
    SUT.axes.resize(3);
    ASSERT_GT(SUT.pretty().size(), 0);
}