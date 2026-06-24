
#include <StandardMsg.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages::Standard;
TEST(MsgCovariance6D, DefaultZeroConstructor) {
  Covariance6DMsg SUT;
  ASSERT_EQ(SUT.covariance.size(), 36);
}
