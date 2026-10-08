/**
 * @compare_tag Process-SourceTest v0.1
 *
 */

#include <gtest/gtest.h>
#include <stdio.h>

#include <SensorHealthMonitorProcess.hpp>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorHealthMonitor;
#include <Infrastructure/Logger.hpp>

TEST(SensorHealthMonitorProcess, Tests) {
    SensorHealthMonitorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
    auto diagnostics = SUT.getDiagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    for (auto diagnostic : diagnostics) {
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }

    fast::rf::Logger::logDebug(SUT.pretty());
}
TEST(SensorHealthMonitorProcess, ConversionTests) {
    SensorHealthMonitorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);
}

TEST(SensorHealthMonitorProcess, SignalHealth) {
    SensorHealthMonitorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);
    double expectedSignalRate = 10.0;
    std::string signalName = "test_signal";
    ASSERT_TRUE(SUT.addSignalToMonitor(signalName, "test_datatype", expectedSignalRate, 90.0));
    double runTime = 10.0;
    double dt = 1.0 / expectedSignalRate;
    double currentTime = 0.0;
    while (currentTime < runTime) {
        fast::rf::messages::SensorMsgs::PointCloudMsg msg;
        msg.time_stamp = currentTime;
        ASSERT_TRUE(SUT.newPointCloud(signalName, msg));
        ASSERT_TRUE(SUT.update(currentTime));
        currentTime += dt;
    }
    auto diagnostics = SUT.getDiagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    for (auto diagnostic : diagnostics) {
        ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
}