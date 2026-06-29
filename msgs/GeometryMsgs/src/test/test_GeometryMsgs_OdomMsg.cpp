
#include <OdomMsg.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages::GeometryMsgs;

TEST(OdomMsg, DefaultZeroConstructor) {
  OdomMsg SUT;
  // Nothing new to test
}