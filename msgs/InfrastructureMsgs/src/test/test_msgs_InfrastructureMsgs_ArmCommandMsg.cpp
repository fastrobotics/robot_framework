
#include <gtest/gtest.h>
#include <stdio.h>

#include <ArmCommandMsg.hpp>
using namespace fast::rf::messages::InfrastructureMsgs;
TEST(ArmCommandMsg, DefaultZeroConstructor) {
    ArmCommandMsg SUT;
    ASSERT_TRUE(true);
}