#include <gtest/gtest.h>

#include <RobotFrameworkDefinitions.hpp>
using namespace fast::rf;
TEST(BasicDefinitions, BasicAssertions) {
    for (uint8_t i = 0; i < (uint8_t)fast::rf::Level::END_OF_LIST; ++i) {
        std::string str = fast::rf::pretty((fast::rf::Level)i);
        if ((i == (uint8_t)fast::rf::Level::UNKNOWN) || (i == (uint8_t)fast::rf::Level::END_OF_LIST)) {
            ASSERT_EQ(str, "UNKNOWN");
        } else {
            printf("%d %s\n", i, str.c_str());
            ASSERT_NE(str, "UNKNOWN");
        }
    }
}