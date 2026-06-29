
#include <gtest/gtest.h>
#include <stdio.h>

#include <GlobalPathCommandMsg.hpp>
using namespace fast::rf::messages::NavMsgs;
TEST(GlobalPathCommandMsg, DefaultZeroConstructor) {
    GlobalPathCommandMsg SUT;
    ASSERT_FALSE(SUT.ok());
    SUT.path_uuid = 1;
    ASSERT_TRUE(SUT.ok());
}