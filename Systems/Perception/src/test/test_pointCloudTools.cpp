#pragma GCC optimize("O3,inline,fast-math")

#include <gtest/gtest.h>

#include <Infrastructure/Logger.hpp>
#include <PointCloudTools.hpp>
#include <chrono>
#include <random>

using namespace fast::rf::PerceptionSystem;
using namespace fast::rf::messages::SensorMsgs;

// Helper to generate a realistic mock message matching PCL structure step sizes
PointCloudMsg createTestRgbdMessage(uint32_t num_points) {
    PointCloudMsg msg;
    msg.time_stamp = 123456789.012;
    msg.height = 1;
    msg.width = num_points;
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

// 1. Test standard conversions and round-trip data preservation
TEST(PointCloudTools, RoundTripConversionSuccess) {
    const uint32_t kNumPoints = 1000;
    PointCloudMsg original_msg = createTestRgbdMessage(kNumPoints);

    // Convert Msg -> PCL
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcl_cloud;
    ASSERT_NO_THROW(convertToPCL<pcl::PointXYZRGB>(original_msg, pcl_cloud));

    // Assert PCL cloud structural characteristics
    ASSERT_NE(pcl_cloud, nullptr);
    EXPECT_EQ(pcl_cloud->width, original_msg.width);
    EXPECT_EQ(pcl_cloud->height, original_msg.height);
    EXPECT_EQ(pcl_cloud->points.size(), kNumPoints);

    // Convert PCL -> Msg
    PointCloudMsg output_msg;
    ASSERT_NO_THROW(convertFromPCL<pcl::PointXYZRGB>(pcl_cloud, output_msg));

    // Assert outbound metadata matching characteristics
    EXPECT_EQ(output_msg.width, original_msg.width);
    EXPECT_EQ(output_msg.height, original_msg.height);
    EXPECT_NEAR(output_msg.time_stamp, original_msg.time_stamp, 1e-4);
    EXPECT_EQ(output_msg.point_step, original_msg.point_step);
    EXPECT_EQ(output_msg.data.size(), original_msg.data.size());

    // Deep data byte-array verification to prove zero data loss / distortion
    EXPECT_EQ(output_msg.data, original_msg.data);
}

// 2. Edge Case Test: Empty Point Clouds
TEST(PointCloudTools, HandleEmptyCloudsGracefully) {
    PointCloudMsg empty_msg = createTestRgbdMessage(0);

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcl_cloud;
    ASSERT_NO_THROW(convertToPCL<pcl::PointXYZRGB>(empty_msg, pcl_cloud));

    ASSERT_NE(pcl_cloud, nullptr);
    EXPECT_EQ(pcl_cloud->points.size(), 0);

    PointCloudMsg output_msg;
    ASSERT_NO_THROW(convertFromPCL<pcl::PointXYZRGB>(pcl_cloud, output_msg));
    EXPECT_EQ(output_msg.width, 0);
    EXPECT_TRUE(output_msg.data.empty());
}

// 3. Performance Benchmark Test: Ensure conversion is running at sub-millisecond speeds
TEST(PointCloudTools, ConversionPerformanceBenchmark) {
    // 300k points mimics a dense 640x480 RealSense / Kinect depth map frame
    const uint32_t kDenseFramePoints = 300000;
    PointCloudMsg dense_msg = createTestRgbdMessage(kDenseFramePoints);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcl_cloud;

    auto start_time = std::chrono::high_resolution_clock::now();
    convertToPCL<pcl::PointXYZRGB>(dense_msg, pcl_cloud);
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration_ms = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() / 1000.0;

    std::cout << "[ BENCHMARK ] Msg->PCL conversion for " << kDenseFramePoints
              << " points completed in: " << duration_ms << " ms" << std::endl;

    // Enforce that your optimized conversion completes well within real-time budgets (e.g. < 2.5 milliseconds)
    EXPECT_LT(duration_ms, 10.0);
}
