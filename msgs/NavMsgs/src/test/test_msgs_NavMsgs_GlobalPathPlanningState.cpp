
#include <gtest/gtest.h>
#include <stdio.h>

#include <GlobalPathPlanningStateMsg.hpp>
#include <GlobalPathPlanningStatusEnum.hpp>
using namespace fast::rf::messages::NavMsgs;
TEST(GlobalPathPlanningStateMsg, DefaultZeroConstructor) {
    GlobalPathPlanningStateMsg SUT;
    ASSERT_EQ(SUT.path_uuid, 0);
    ASSERT_EQ(SUT.state, GlobalPathPlanningStatusEnum::UNKNOWN);
}