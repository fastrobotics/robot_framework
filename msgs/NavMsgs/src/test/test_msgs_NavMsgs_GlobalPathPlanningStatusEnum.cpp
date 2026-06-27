
#include <GlobalPathPlanningStatusEnum.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages::NavMsgs;
TEST(GlobalPathPlanningStatusEnum, ConvertStateToString) {
  for (uint8_t i = (uint8_t)GlobalPathPlanningStatusEnum::UNKNOWN;
       i < (uint8_t)GlobalPathPlanningStatusEnum::END_OF_LIST; ++i) {
    std::string str = convert((GlobalPathPlanningStatusEnum)i);
    ASSERT_NE(str, "");
  }
}