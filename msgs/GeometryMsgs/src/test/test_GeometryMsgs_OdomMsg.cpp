
#include <gtest/gtest.h>
#include <stdio.h>

#include <OdomMsg.hpp>
using namespace fast::rf::messages::GeometryMsgs;

TEST(OdomMsg, DefaultZeroConstructor) {
    OdomMsg SUT;
    // Nothing new to test
}