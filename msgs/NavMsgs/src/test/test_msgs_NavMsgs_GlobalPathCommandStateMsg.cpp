
#include <gtest/gtest.h>
#include <stdio.h>

#include <GlobalPathCommandStateMsg.hpp>
#include <GlobalPathCommandStatusEnum.hpp>
using namespace fast::rf::messages::NavMsgs;
TEST(GlobalPathCommandStateMsg, DefaultZeroConstructor) {
    GlobalPathCommandStateMsg SUT;
    ASSERT_EQ(SUT.path_uuid, 0);
    ASSERT_EQ(SUT.state, GlobalPathCommandStatusEnum::UNKNOWN);
}