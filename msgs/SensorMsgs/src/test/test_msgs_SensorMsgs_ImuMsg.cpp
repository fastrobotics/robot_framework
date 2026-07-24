
#include <gtest/gtest.h>
#include <stdio.h>

#include <ImuMsg.hpp>
#include <Infrastructure/Logger.hpp>
using namespace fast::rf::messages::SensorMsgs;
TEST(ImuMsg, DefaultZeroConstructor) {
    ImuMsg SUT;
    ASSERT_GT(SUT.pretty().size(), 0);
}