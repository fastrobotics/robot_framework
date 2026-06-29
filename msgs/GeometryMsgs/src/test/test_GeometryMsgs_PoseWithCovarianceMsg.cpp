
#include <gtest/gtest.h>
#include <stdio.h>

#include <PoseWithCovarianceMsg.hpp>
using namespace fast::rf::messages::GeometryMsgs;

TEST(PoseWithCovarianceMsg, DefaultZeroConstructor) {
    PoseWithCovarianceMsg SUT;
    ASSERT_LT(SUT.covariance.covariance[PoseWithCovarianceMsg::COV_X], 0.0);
    ASSERT_LT(SUT.covariance.covariance[PoseWithCovarianceMsg::COV_Y], 0.0);
    ASSERT_LT(SUT.covariance.covariance[PoseWithCovarianceMsg::COV_Z], 0.0);
    ASSERT_LT(SUT.covariance.covariance[PoseWithCovarianceMsg::COV_ROLL], 0.0);
    ASSERT_LT(SUT.covariance.covariance[PoseWithCovarianceMsg::COV_PITCH], 0.0);
    ASSERT_LT(SUT.covariance.covariance[PoseWithCovarianceMsg::COV_YAW], 0.0);
}