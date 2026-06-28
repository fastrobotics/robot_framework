
#include <GlobalPathCommandStatusEnum.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages::NavMsgs;
TEST(GlobalPathCommandStatusEnum, ConvertStateToString) {
  for (uint8_t i = (uint8_t)GlobalPathCommandStatusEnum::UNKNOWN;
       i < (uint8_t)GlobalPathCommandStatusEnum::END_OF_LIST; ++i) {
    std::string str = convert((GlobalPathCommandStatusEnum)i);
    ASSERT_NE(str, "");
  }
}