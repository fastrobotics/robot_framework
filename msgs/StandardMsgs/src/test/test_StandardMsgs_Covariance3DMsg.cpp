
#include <gtest/gtest.h>
#include <stdio.h>

#include <Covariance3DMsg.hpp>
using namespace fast::rf::messages::StandardMsgs;
TEST(Covariance3DMsg, DefaultZeroConstructor) {
    Covariance3DMsg SUT;
    ASSERT_EQ(SUT.covariance.size(), Covariance3DMsg::DIMENSION * Covariance3DMsg::DIMENSION);
    ASSERT_LT(SUT.covariance[Covariance3DMsg::X1], 0.0);
    ASSERT_LT(SUT.covariance[Covariance3DMsg::X2], 0.0);
    ASSERT_LT(SUT.covariance[Covariance3DMsg::X3], 0.0);
}