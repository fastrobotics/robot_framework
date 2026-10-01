
#include <gtest/gtest.h>
#include <stdio.h>

#include <PointCloudMsg.hpp>
using namespace fast::rf::messages::SensorMsgs;
TEST(PointCloudMsg, DefaultZeroConstructor) {
    PointCloudMsg SUT;
    ASSERT_LT(SUT.time_stamp, 0);
    ASSERT_EQ(SUT.seq, 0);
}
TEST(PointCloudMsg, PrettyFunctions) {
    PointCloudMsg SUT;
    ASSERT_GT(SUT.pretty().size(), 0);
}