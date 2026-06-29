
#include <gtest/gtest.h>
#include <stdio.h>

#include <TwistMsg.hpp>
using namespace fast::rf::messages::GeometryMsgs;

TEST(TwistMsg, DefaultZeroConstructor) {
    TwistMsg SUT;
    // Nothing new to test
}