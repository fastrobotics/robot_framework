
#include <GlobalPathCommandMsg.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages::NavMsgs;
TEST(GlobalPathCommandMsg, DefaultZeroConstructor) {
  GlobalPathCommandMsg SUT;
  ASSERT_FALSE(SUT.ok());
}