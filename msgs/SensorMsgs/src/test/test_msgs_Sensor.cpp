
#include "SensorMsgs.hpp"

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages::SensorMsgs;
TEST(GlobalPositionSensorData, BasicAssertions) {
  {
    GlobalPositionSensorData SUT;
    ASSERT_TRUE(SUT.ok());
  }
  {
    GlobalPositionSensorData SUT;
    SUT.latitude_deg = GlobalPositionSensorData::MAX_ANGLE + 0.1;
    ASSERT_FALSE(SUT.ok());
  }
  {
    GlobalPositionSensorData SUT;
    SUT.latitude_deg = GlobalPositionSensorData::MIN_ANGLE - 0.1;
    ASSERT_FALSE(SUT.ok());
  }
  {
    GlobalPositionSensorData SUT;
    SUT.longitude_deg = GlobalPositionSensorData::MAX_ANGLE + 0.1;
    ASSERT_FALSE(SUT.ok());
  }
  {
    GlobalPositionSensorData SUT;
    SUT.longitude_deg = GlobalPositionSensorData::MIN_ANGLE - 0.1;
    ASSERT_FALSE(SUT.ok());
  }
}