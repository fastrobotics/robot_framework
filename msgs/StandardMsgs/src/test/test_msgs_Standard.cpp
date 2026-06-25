
#include <StandardMsgs.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages::StandardMsgs;
TEST(MsgCovariance6D, DefaultZeroConstructor) {
  Covariance6DMsg SUT;
  ASSERT_EQ(SUT.covariance.size(),
            Covariance6DMsg::DIMENSION * Covariance6DMsg::DIMENSION);
  ASSERT_LT(SUT.covariance[Covariance6DMsg::X1], 0.0);
  ASSERT_LT(SUT.covariance[Covariance6DMsg::X2], 0.0);
  ASSERT_LT(SUT.covariance[Covariance6DMsg::X3], 0.0);
  ASSERT_LT(SUT.covariance[Covariance6DMsg::X4], 0.0);
  ASSERT_LT(SUT.covariance[Covariance6DMsg::X5], 0.0);
  ASSERT_LT(SUT.covariance[Covariance6DMsg::X6], 0.0);
}
