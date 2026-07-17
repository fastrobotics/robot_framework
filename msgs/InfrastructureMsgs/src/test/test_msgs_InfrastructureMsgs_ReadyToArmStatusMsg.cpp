
#include <gtest/gtest.h>
#include <stdio.h>

#include <ReadyToArmStatusMsg.hpp>
using namespace fast::rf::messages::InfrastructureMsgs;
TEST(ReadyToArmStatusMsg, DefaultZeroConstructor) {
    ReadyToArmStatusMsg SUT;
    ASSERT_TRUE(false);
}