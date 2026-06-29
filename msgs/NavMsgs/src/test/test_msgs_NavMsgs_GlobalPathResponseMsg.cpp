
#include <gtest/gtest.h>
#include <stdio.h>

#include <GlobalPathPlanningStatusEnum.hpp>
#include <GlobalPathResponseMsg.hpp>
using namespace fast::rf::messages::NavMsgs;
TEST(GlobalPathResponse, DefaultZeroConstructor) {
    GlobalPathResponse resp;
    ASSERT_EQ(resp.path_uuid, 0);
    ASSERT_EQ(resp.state, GlobalPathPlanningStatusEnum::UNKNOWN);
}