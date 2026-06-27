
#include <GlobalPathRequestMsg.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages::NavMsgs;
TEST(GlobalPathRequest, DefaultZeroConstructor) {
  GlobalPathRequest req;
  ASSERT_EQ(req.pass_thru_points.size(), 0);
  ASSERT_FALSE(req.ok()); // Invalid Reqeust, no path id
}