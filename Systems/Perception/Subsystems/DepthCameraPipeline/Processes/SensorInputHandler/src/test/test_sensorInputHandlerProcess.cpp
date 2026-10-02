/**
 * @compare_tag Process-SourceTest v0.1
 *
 */

#include <gtest/gtest.h>
#include <stdio.h>

#include <SensorInputHandlerProcess.hpp>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorInputHandler;
#include <Infrastructure/Logger.hpp>

TEST(SensorInputHandlerProcess, Tests) {
    SensorInputHandlerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
    auto diagnostics = SUT.getDiagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    for (auto diagnostic : diagnostics) {
        // ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
    fast::rf::Logger::logDebug(SUT.pretty());
}
TEST(SensorInputHandlerProcess, ConversionTests) {
    SensorInputHandlerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);
}
