
#include <gtest/gtest.h>
#include <stdio.h>

#include <AccelMsg.hpp>
using namespace fast::rf::messages::GeometryMsgs;
TEST(AccelMsg, DefaultZeroConstructor) {
    AccelMsg SUT;
    // Nothing new to test
}
TEST(AccelMsg, SupportFunctions) {
    AccelMsg SUT;
    printf("%s\n", SUT.pretty().c_str());
    ASSERT_GT(SUT.pretty().size(), 0);
}