
#include <gtest/gtest.h>
#include <stdio.h>

#include <GlobalPathCommandMsg.hpp>
using namespace fast::rf::messages::NavMsgs;
TEST(GlobalPathCommandMsg, DefaultZeroConstructor) {
    GlobalPathCommandMsg SUT;
    ASSERT_FALSE(SUT.ok());
}