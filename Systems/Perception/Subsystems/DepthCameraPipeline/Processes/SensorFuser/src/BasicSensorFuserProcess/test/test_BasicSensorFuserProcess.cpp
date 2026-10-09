/**
 * @compare_tag Process-BasicSourceTest v0.1
 *
 */

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicSensorFuserProcess/BasicSensorFuserProcess.hpp>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser;
#include <Infrastructure/Logger.hpp>

TEST(BasicSensorFuserProcess, BasicTests) {
    BasicSensorFuserProcess SUT;
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
TEST(BasicSensorFuserProcess, BasicConversionTests) {
    BasicSensorFuserProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);
}
TEST(BasicSensorFuserProcess, BasicOperations) {
    BasicSensorFuserProcess SUT;
    ASSERT_TRUE(SUT.init());

    double runTime = SUT.getConfig().m_settleTimeSec * 2.0;
    double currentTime = 0.0;
    double dt = 0.1;
    while (currentTime <= runTime) {
        fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud;
        sensorCloud.time_stamp = 1.234;
        ASSERT_TRUE(SUT.newPointCloud(sensorCloud, 0));
        ASSERT_TRUE(SUT.update(currentTime));
        fast::rf::Logger::logDebug(SUT.pretty());
        currentTime += dt;
    }
    auto diagnostics = SUT.getDiagnostics();
    for (auto diagnostic : diagnostics) {
        ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
}