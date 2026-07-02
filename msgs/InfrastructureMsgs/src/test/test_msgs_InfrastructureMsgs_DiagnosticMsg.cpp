
#include <gtest/gtest.h>
#include <stdio.h>

#include <DiagnosticMsg.hpp>
using namespace fast::rf::messages::InfrastructureMsgs;
TEST(DiagnosticMsg, DefaultZeroConstructor) {
    DiagnosticMsg SUT;
    ASSERT_TRUE(true);
}