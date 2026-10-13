/**
 * @compare_tag Process-SourceTest v0.1
 *
 */

#include <gtest/gtest.h>
#include <stdio.h>

#include <SensorInputHandlerProcess.hpp>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorInputHandler;
#include <Infrastructure/Logger.hpp>

TEST(SensorInputHandlerProcess, BasicTests) {
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
TEST(SensorInputHandlerProcess, TestFailConvertUnorganizedPointCloud) {
    SensorInputHandlerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);

    fast::rf::messages::SensorMsgs::PointCloudMsg unorganizedPointCloud;
    unorganizedPointCloud.point_cloud->height = 1;
    auto convertedCloud = SUT.newPointCloud(unorganizedPointCloud);
    ASSERT_EQ(convertedCloud.point_cloud->height, 0);  // Don't know how to process this, so return an empty cloud
    auto diagnostics = SUT.getDiagnostics();
    bool checkFailedDiagnostic = false;
    for (auto diagnostic : diagnostics) {
        if (diagnostic.diagnosticType == fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS) {
            ASSERT_GT(diagnostic.level, fast::rf::Level::NOTICE);
            checkFailedDiagnostic = true;
        }
    }
    ASSERT_TRUE(checkFailedDiagnostic);
}
TEST(SensorInputHandlerProcess, ConvertOrganizedPointCloudPassThru) {
    SensorInputHandlerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);

    fast::rf::messages::SensorMsgs::PointCloudMsg organizedPointCloud;
    organizedPointCloud.point_cloud->height = 2;
    organizedPointCloud.point_cloud->width = 1;
    organizedPointCloud.point_cloud->points.resize(2);
    auto convertedCloud = SUT.newPointCloud(organizedPointCloud);
    ASSERT_EQ(convertedCloud.point_cloud->height, organizedPointCloud.point_cloud->height);
    ASSERT_TRUE(SUT.update(1.0));
    fast::rf::Logger::logDebug(SUT.pretty());
    auto diagnostics = SUT.getDiagnostics();
    for (auto diagnostic : diagnostics) {
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
        ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
    }
}