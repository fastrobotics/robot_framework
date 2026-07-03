
#include <gtest/gtest.h>

#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
using namespace fast::rf::core::infrastructure;
TEST(DiagnosticManager, BasicAssertions) {
    DiagnosticManager SUT;
    ASSERT_TRUE(SUT.init());
}