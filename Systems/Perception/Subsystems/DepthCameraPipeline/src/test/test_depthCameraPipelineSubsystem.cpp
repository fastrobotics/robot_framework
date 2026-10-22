#include <gtest/gtest.h>
#include <stdio.h>

#include <DepthCameraPipelineSubsystem.hpp>
#include <chrono>
#include <random>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem;
#include <Infrastructure/Logger.hpp>

fast::rf::messages::SensorMsgs::PointCloudMsg createTestRgbdMessage(double time_stamp, uint16_t width,
                                                                    uint16_t height) {
    fast::rf::messages::SensorMsgs::PointCloudMsg msg;
    msg.time_stamp = time_stamp;
    msg.point_cloud->height = height;
    msg.point_cloud->width = width;
    uint64_t num_points = width * height;
    msg.point_cloud->is_dense = false;
    msg.point_cloud->points.resize(num_points);

    for (uint32_t i = 0; i < num_points; ++i) {
        auto& point = msg.point_cloud->points[i];
        const uint32_t column = i % width;
        const uint32_t row = i / width;
        const float depth = 2.0f + 0.1f * std::sin(column * 0.02f) + 0.06f * std::sin(row * 0.025f);
        point.x = (static_cast<float>(column) - 319.5f) * depth / 525.0f;
        point.y = (239.5f - static_cast<float>(row)) * depth / 525.0f;
        point.z = depth;
        if (i % 1000 == 0)
            point.x = std::numeric_limits<float>::quiet_NaN();
        if (i % 10000 == 5000) {
            const uint32_t spike_index = i / 10000;
            point.x = 1.5f + (spike_index % 8) * 0.15f;
            point.y = 1.5f + (spike_index / 8) * 0.15f;
            point.z = 3.0f;
        }
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
    fast::rf::messages::SensorMsgs::PointCloudMsg pointCloud = createTestRgbdMessage(1.0, 640 * 3, 480 * 3);
    std::string signalName = "sensor1";

    ASSERT_TRUE(SUT.addSignalToMonitor(signalName, "sensor_msgs/msg/PointCloud2", 20.0, 50.0));
    ASSERT_TRUE(SUT.newPointCloud(pointCloud, signalName));
    fast::rf::Logger::logInfo(SUT.pretty());
    ASSERT_TRUE(SUT.update(1.0));
    const auto initialTimings = SUT.getUpdateTimings();
    EXPECT_FALSE(initialTimings.pipelineExecuted);
    EXPECT_DOUBLE_EQ(initialTimings.featureDetectionSec, 0.0);
    EXPECT_DOUBLE_EQ(initialTimings.objectDetectionSec, 0.0);
    EXPECT_DOUBLE_EQ(initialTimings.outputUpdateSec, 0.0);
    ASSERT_TRUE(SUT.update(2.0));
    const auto timings = SUT.getUpdateTimings();
    ASSERT_TRUE(timings.pipelineExecuted);
    EXPECT_GE(timings.fusedOutputRetrievalSec, 0.0);
    EXPECT_GE(timings.featureDetectionSec, 0.0);
    EXPECT_GE(timings.objectDetectionSec, 0.0);
    EXPECT_GE(timings.outputUpdateSec, 0.0);
    EXPECT_GE(timings.processUpdatesSec, 0.0);
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

TEST(DepthCameraPipelineSubsystem, UpdateTimingsRunningAverage) {
    DepthCameraPipelineSubsystem::UpdateTimings timings;
    DepthCameraPipelineSubsystem::UpdateTimings sample;
    sample.fusedOutputRetrievalSec = 2.0;
    sample.featureDetectionSec = 4.0;
    sample.objectDetectionSec = 6.0;
    sample.outputUpdateSec = 8.0;
    sample.totalSec = 20.0;
    sample.pipelineExecuted = true;
    timings.addSample(sample);

    sample.fusedOutputRetrievalSec = 4.0;
    sample.featureDetectionSec = 0.0;
    sample.objectDetectionSec = 0.0;
    sample.outputUpdateSec = 0.0;
    sample.totalSec = 2.0;
    sample.pipelineExecuted = false;
    timings.addSample(sample);

    EXPECT_DOUBLE_EQ(timings.fusedOutputRetrievalSec, 3.0);
    EXPECT_DOUBLE_EQ(timings.featureDetectionSec, 4.0);
    EXPECT_DOUBLE_EQ(timings.objectDetectionSec, 6.0);
    EXPECT_DOUBLE_EQ(timings.outputUpdateSec, 8.0);
    EXPECT_DOUBLE_EQ(timings.totalSec, 11.0);
    EXPECT_FALSE(timings.pipelineExecuted);
    EXPECT_NE(timings.pretty().find("timing averages (s"), std::string::npos);
    EXPECT_EQ(timings.pretty().find("(ms"), std::string::npos);
}