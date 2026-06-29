
#include <PoseMsg.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages::GeometryMsgs;

TEST(PoseMsg, DefaultZeroConstructor) {
  PoseMsg SUT;
  // Nothing new to test
}