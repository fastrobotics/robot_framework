#include <gtest/gtest.h>
#include <stdio.h>

#include <DepthCameraPipelineSubsystem.hpp>
#include <chrono>
#include <random>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem;
#include <Infrastructure/Logger.hpp>

fast::rf::messages::SensorMsgs::PointCloudMsg createTestRgbdMessage(uint32_t num_points) {
    fast::rf::messages::SensorMsgs::PointCloudMsg msg;
    msg.time_stamp = 123456789.012;
    msg.height = 2;
    msg.width = num_points / msg.height;
    msg.is_bigendian = false;
    msg.point_step = sizeof(pcl::PointXYZRGB);  // 32 bytes due to Eigen alignments
    msg.row_step = msg.point_step * msg.width;

    // Allocate the contiguous memory payload space
    msg.data.resize(msg.row_step * msg.height);
    if (num_points == 0)
        return msg;

    pcl::PointXYZRGB* points_ptr = reinterpret_cast<pcl::PointXYZRGB*>(msg.data.data());

    std::mt19937 gen(42);  // Fixed seed for reproducible test coordinates
    std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

    for (uint32_t i = 0; i < num_points; ++i) {
        points_ptr[i].x = dist(gen);
        points_ptr[i].y = dist(gen);
        points_ptr[i].z = dist(gen);

        uint8_t r = static_cast<uint8_t>(i % 256);
        uint8_t g = static_cast<uint8_t>((i + 50) % 256);
        uint8_t b = static_cast<uint8_t>((i + 100) % 256);

        uint32_t rgb = (static_cast<uint32_t>(r) << 16 | static_cast<uint32_t>(g) << 8 | static_cast<uint32_t>(b));
        std::memcpy(&points_ptr[i].rgb, &rgb, sizeof(float));
    }

    return msg;
}
TEST(DepthCameraPipelineSubsystem, BasicTests) {
    DepthCameraPipelineSubsystem SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);
    fast::rf::Logger::logInfo(SUT.pretty());
    fast::rf::messages::SensorMsgs::PointCloudMsg pointCloud = createTestRgbdMessage(1000);
    std::string signalName = "sensor1";
    ASSERT_TRUE(SUT.addSignalToMonitor(signalName, "sensor_msgs/msg/PointCloud2", 20.0, 50.0));
    ASSERT_TRUE(SUT.newPointCloud(pointCloud, signalName));
    ASSERT_TRUE(SUT.update(0.0));
    const auto fusedPointCloud = SUT.getFusedPointCloud();
    ASSERT_DOUBLE_EQ(fusedPointCloud.time_stamp, pointCloud.time_stamp);
    auto readyToArm = SUT.get_ready_to_arm();
    ASSERT_GT(readyToArm.systemID, 0);
    ASSERT_GT(readyToArm.subsystemID, 0);
    ASSERT_EQ(readyToArm.processID, 0);
    ASSERT_FALSE(readyToArm.ready_to_arm);
    auto diagnostics = SUT.getDiagnostics();
    ASSERT_GT(diagnostics.size(), 0);
}