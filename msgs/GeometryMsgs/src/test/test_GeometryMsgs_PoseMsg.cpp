
#include <gtest/gtest.h>
#include <stdio.h>

#include <PoseMsg.hpp>
using namespace fast::rf::messages::GeometryMsgs;

TEST(PoseMsg, DefaultZeroConstructor) {
    PoseMsg SUT;
    // Nothing new to test
}