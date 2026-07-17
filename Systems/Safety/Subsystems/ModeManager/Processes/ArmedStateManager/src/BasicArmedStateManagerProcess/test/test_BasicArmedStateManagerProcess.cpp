

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicArmedStateManagerProcess/BasicArmedStateManagerProcess.hpp>

using namespace fast::rf::SafetySystem::ModeManagerSubsystem;

TEST(BasicArmedStateManagerProcess, BasicTests) {
    BasicArmedStateManagerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0, 0.0));
    auto diagnostics = SUT.get_diagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    for (auto diagnostic : diagnostics) {
        ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
}
TEST(BasicArmedStateManagerProcess, BasicConversionTests) {
    BasicArmedStateManagerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(true);
}