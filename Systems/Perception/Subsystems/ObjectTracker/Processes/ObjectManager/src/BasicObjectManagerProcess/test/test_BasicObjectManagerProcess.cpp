/**
 * @compare_tag Process-BasicSourceTest v0.1
 *
 */

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicObjectManagerProcess/BasicObjectManagerProcess.hpp>

using namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::ObjectManager;
#include <Infrastructure/Logger.hpp>

TEST(BasicObjectManagerProcess, BasicTests) {
    BasicObjectManagerProcess sut;
    ASSERT_TRUE(sut.init());
    ASSERT_TRUE(sut.update(0.0));
    auto diagnostics = sut.getDiagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    for (auto diagnostic : diagnostics) {
        ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
    ASSERT_TRUE(sut.getReadyToArm().ready_to_arm);
    fast::rf::Logger::logDebug(sut.pretty());
}
TEST(BasicObjectManagerProcess, BasicConversionTests) {
    BasicObjectManagerProcess sut;
    ASSERT_TRUE(sut.init());
    ASSERT_GT(sut.pretty().size(), 0);
}
