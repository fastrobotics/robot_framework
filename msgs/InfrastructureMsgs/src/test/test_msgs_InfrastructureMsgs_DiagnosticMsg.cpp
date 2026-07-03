
#include <gtest/gtest.h>
#include <stdio.h>

#include <DiagnosticMsg.hpp>
using namespace fast::rf::messages::InfrastructureMsgs;
TEST(DiagnosticMsg, DefaultZeroConstructor) {
    DiagnosticMsg SUT(1, 2, 3, fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
    ASSERT_TRUE(true);
}