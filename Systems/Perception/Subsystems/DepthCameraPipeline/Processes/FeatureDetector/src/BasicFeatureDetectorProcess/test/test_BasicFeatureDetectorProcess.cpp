/**
 * @compare_tag Process-BasicSourceTest v0.1
 *
 */

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicFeatureDetectorProcess/BasicFeatureDetectorProcess.hpp>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector;
#include <Infrastructure/Logger.hpp>

TEST(BasicFeatureDetectorProcess, BasicTests) {
    BasicFeatureDetectorProcess SUT;
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
TEST(BasicFeatureDetectorProcess, BasicConversionTests) {
    BasicFeatureDetectorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);
}
