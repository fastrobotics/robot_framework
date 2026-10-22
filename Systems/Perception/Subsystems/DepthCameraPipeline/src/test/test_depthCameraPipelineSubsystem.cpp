#include <gtest/gtest.h>
#include <stdio.h>

#include <DepthCameraPipelineSubsystem.hpp>
#include <chrono>
#include <random>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem;
#include <Infrastructure/Logger.hpp>

fast::rf::messages::SensorMsgs::PointCloudMsg createTestRgbdMessage(double time_stamp, uint32_t num_points) {
    fast::rf::messages::SensorMsgs::PointCloudMsg msg;
    msg.time_stamp = time_stamp;
    msg.point_cloud->height = num_points >= 2 && num_points % 2 == 0 ? 2 : 1;
    msg.point_cloud->width = num_points / msg.point_cloud->height;
    msg.point_cloud->points.resize(num_points);

    std::mt19937 gen(42);  // Fixed seed for reproducible test coordinates
    std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

    for (uint32_t i = 0; i < num_points; ++i) {
        auto& point = msg.point_cloud->points[i];
        point.x = dist(gen);
        point.y = dist(gen);
        point.z = dist(gen);
        point.r = static_cast<uint8_t>(i % 256);
        point.g = static_cast<uint8_t>((i + 50) % 256);
        point.b = static_cast<uint8_t>((i + 100) % 256);
    }

    return msg;
}
TEST(DepthCameraPipelineSubsystem, BasicTests) {
    DepthCameraPipelineSubsystem SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);
    fast::rf::messages::SensorMsgs::PointCloudMsg pointCloud = createTestRgbdMessage(1.0, 1000);
    std::string signalName = "sensor1";

    ASSERT_TRUE(SUT.addSignalToMonitor(signalName, "sensor_msgs/msg/PointCloud2", 20.0, 50.0));
    ASSERT_TRUE(SUT.newPointCloud(pointCloud, signalName));
    fast::rf::Logger::logInfo(SUT.pretty());
    ASSERT_TRUE(SUT.update(1.0));
    const auto initialTimings = SUT.getLastUpdateTimings();
    EXPECT_FALSE(initialTimings.visionPipelineExecuted);
    EXPECT_DOUBLE_EQ(initialTimings.featureDetectionSec, 0.0);
    EXPECT_DOUBLE_EQ(initialTimings.objectDetectionSec, 0.0);
    EXPECT_DOUBLE_EQ(initialTimings.outputUpdateSec, 0.0);
    ASSERT_TRUE(SUT.update(2.0));
    const auto timings = SUT.getLastUpdateTimings();
    ASSERT_TRUE(timings.visionPipelineExecuted);
    EXPECT_GE(timings.fusedOutputRetrievalSec, 0.0);
    EXPECT_GE(timings.featureDetectionSec, 0.0);
    EXPECT_GE(timings.objectDetectionSec, 0.0);
    EXPECT_GE(timings.outputUpdateSec, 0.0);
    EXPECT_GE(timings.processUpdatesSec, 0.0);
    EXPECT_GE(timings.totalSec, timings.fusedOutputRetrievalSec + timings.featureDetectionSec +
                                    timings.objectDetectionSec + timings.outputUpdateSec + timings.processUpdatesSec);
    fast::rf::Logger::logInfo(SUT.pretty());
    auto readyToArm = SUT.get_ready_to_arm();
    ASSERT_GT(readyToArm.systemID, 0);
    ASSERT_GT(readyToArm.subsystemID, 0);
    ASSERT_EQ(readyToArm.processID, 0);
    ASSERT_FALSE(readyToArm.ready_to_arm);
    auto diagnostics = SUT.getDiagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    auto output = SUT.getOutput();
    ASSERT_GT(output.fullPipelineOutputCounter, 0);
}