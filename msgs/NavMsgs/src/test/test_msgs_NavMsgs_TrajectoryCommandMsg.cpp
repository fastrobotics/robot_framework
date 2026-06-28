
#include <TrajectoryCommandMsg.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages::NavMsgs;
TEST(TrajectoryCommandMsg, DefaultZeroConstructor) {
  TrajectoryCommandMsg SUT;
  ASSERT_EQ(SUT.cmd_twists.size(), 0);
}