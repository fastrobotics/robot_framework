
#include <gtest/gtest.h>
#include <stdio.h>

#include <TwistWithCovarianceMsg.hpp>
using namespace fast::rf::messages::GeometryMsgs;

TEST(TwistWithCovarianceMsg, DefaultZeroConstructor) {
    TwistWithCovarianceMsg SUT;
    ASSERT_LT(SUT.covariance.covariance[TwistWithCovarianceMsg::COV_LINEAR_X], 0.0);
    ASSERT_LT(SUT.covariance.covariance[TwistWithCovarianceMsg::COV_LINEAR_Y], 0.0);
    ASSERT_LT(SUT.covariance.covariance[TwistWithCovarianceMsg::COV_LINEAR_Z], 0.0);
    ASSERT_LT(SUT.covariance.covariance[TwistWithCovarianceMsg::COV_ANGULAR_ROLL], 0.0);
    ASSERT_LT(SUT.covariance.covariance[TwistWithCovarianceMsg::COV_ANGULAR_PITCH], 0.0);
    ASSERT_LT(SUT.covariance.covariance[TwistWithCovarianceMsg::COV_ANGULAR_YAW], 0.0);
}
