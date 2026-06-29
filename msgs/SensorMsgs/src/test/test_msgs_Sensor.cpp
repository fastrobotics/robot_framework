
#include <gtest/gtest.h>
#include <stdio.h>

#include "SensorMsgs.hpp"
using namespace fast::rf::messages::SensorMsgs;
TEST(GlobalPositionSensorMsg, BasicAssertions) {
    {
        GlobalPositionSensorMsg SUT;
        ASSERT_TRUE(SUT.ok());
        ASSERT_LT(SUT.covariance.covariance[GlobalPositionSensorMsg::COV_X], 0.0);
        ASSERT_LT(SUT.covariance.covariance[GlobalPositionSensorMsg::COV_Y], 0.0);
        ASSERT_LT(SUT.covariance.covariance[GlobalPositionSensorMsg::COV_Z], 0.0);
    }
    {
        GlobalPositionSensorMsg SUT;
        SUT.latitude_deg = GlobalPositionSensorMsg::MAX_ANGLE + 0.1;
        ASSERT_FALSE(SUT.ok());
    }
    {
        GlobalPositionSensorMsg SUT;
        SUT.latitude_deg = GlobalPositionSensorMsg::MIN_ANGLE - 0.1;
        ASSERT_FALSE(SUT.ok());
    }
    {
        GlobalPositionSensorMsg SUT;
        SUT.longitude_deg = GlobalPositionSensorMsg::MAX_ANGLE + 0.1;
        ASSERT_FALSE(SUT.ok());
    }
    {
        GlobalPositionSensorMsg SUT;
        SUT.longitude_deg = GlobalPositionSensorMsg::MIN_ANGLE - 0.1;
        ASSERT_FALSE(SUT.ok());
    }
}