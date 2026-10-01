
#include <gtest/gtest.h>
#include <stdio.h>

#include <PointCloudMsg.hpp>
#include <PointFieldMsg.hpp>
using namespace fast::rf::messages::SensorMsgs;
TEST(PointCloudMsg, DefaultZeroConstructor) {
    PointCloudMsg SUT;
    ASSERT_LT(SUT.time_stamp, 0);
}
TEST(PointCloudMsg, PrettyFunctions) {
    PointCloudMsg SUT;
    {
        PointFieldMsg field;
        field.name = "a";
        field.datatype = PointFieldMsg::PointFieldDataType::INT8;
        SUT.fields.push_back(field);
    }
    {
        PointFieldMsg field;
        field.name = "b";
        field.datatype = PointFieldMsg::PointFieldDataType::FLOAT32;
        SUT.fields.push_back(field);
    }
    ASSERT_GT(SUT.pretty().size(), 0);
}
TEST(PointCloudMsg, HelperFunctions) {
    PointCloudMsg pointCloud = PointCloudMsg::generateRGBCloud(4);
    ASSERT_GT(pointCloud.fields.size(), 0);
    ASSERT_GT(pointCloud.data.size(), 0);
}