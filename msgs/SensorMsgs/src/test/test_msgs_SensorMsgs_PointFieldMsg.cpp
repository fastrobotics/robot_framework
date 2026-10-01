
#include <gtest/gtest.h>
#include <stdio.h>

#include <PointFieldMsg.hpp>
using namespace fast::rf::messages::SensorMsgs;
TEST(PointFieldMsg, DefaultZeroConstructor) {
    PointFieldMsg SUT;
    ASSERT_EQ(SUT.offset, 0);
    ASSERT_EQ(SUT.count, 0);
    ASSERT_EQ(SUT.name, "");
    ASSERT_EQ(SUT.datatype, PointFieldMsg::PointFieldDataType::UNKNOWN);
}
TEST(PointFieldMsg, PrettyFunctions) {
    for (uint8_t i = 0; i < (uint8_t)PointFieldMsg::PointFieldDataType::END_OF_LIST; ++i) {
        auto type = (PointFieldMsg::PointFieldDataType)i;
        auto type_str = PointFieldMsg::pretty(type);
        if ((type == PointFieldMsg::PointFieldDataType::UNKNOWN) ||
            (type == PointFieldMsg::PointFieldDataType::END_OF_LIST)) {
            ASSERT_EQ(type_str, "UNKNOWN");
        } else {
            ASSERT_NE(type_str, "UNKNOWN");
        }
    }
    PointFieldMsg SUT;
    ASSERT_GT(SUT.pretty().size(), 0);
}