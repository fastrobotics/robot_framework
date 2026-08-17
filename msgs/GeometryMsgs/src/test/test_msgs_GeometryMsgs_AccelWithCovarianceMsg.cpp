
#include <gtest/gtest.h>
#include <stdio.h>

#include <AccelWithCovarianceMsg.hpp>
using namespace fast::rf::messages::GeometryMsgs;
TEST(AccelWithCovarianceMsg, DefaultZeroConstructor) {
    AccelWithCovarianceMsg SUT;
    ASSERT_LT(SUT.time_stamp, 0.0);
}
TEST(AccelWithCovarianceMsg, SupportFunctions) {
    AccelWithCovarianceMsg SUT;
    printf("%s\n", SUT.pretty().c_str());
    ASSERT_GT(SUT.pretty().size(), 0);
}