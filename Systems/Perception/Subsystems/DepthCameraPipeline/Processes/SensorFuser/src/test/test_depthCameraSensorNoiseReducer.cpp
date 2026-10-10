
#include <gtest/gtest.h>
#include <pcl/filters/filter.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/voxel_grid.h>
#include <stdio.h>

#include <NoiseReducer.hpp>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <limits>
#include <numeric>
#include <vector>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser;

fast::rf::messages::SensorMsgs::PointCloudMsg createTestRgbdMessage(uint32_t num_points) {
    fast::rf::messages::SensorMsgs::PointCloudMsg msg;
    msg.time_stamp = 123456789.012;
    constexpr uint32_t image_width = 640;
    msg.point_cloud->height = (num_points == image_width * 480) ? 480 : 1;
    msg.point_cloud->width = num_points / msg.point_cloud->height;
    msg.point_cloud->is_dense = false;
    msg.point_cloud->points.resize(num_points);

    for (uint32_t i = 0; i < num_points; ++i) {
        auto& point = msg.point_cloud->points[i];
        const uint32_t column = i % image_width;
        const uint32_t row = i / image_width;
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
TEST(DepthCameraNoiseReducer, BasicTests) {
    NoiseReducer SUT;
    ASSERT_TRUE(SUT.init());
    fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud = createTestRgbdMessage(307200);
    sensorCloud.time_stamp = 1.234;
    auto cloud = SUT.reduceNoise(sensorCloud);
    ASSERT_FLOAT_EQ(cloud.time_stamp, sensorCloud.time_stamp);
}
TEST(DepthCameraNoiseReducer, ParallelRadiusFilterMatchesPcl) {
    NoiseReducer SUT;
    ASSERT_TRUE(SUT.init());

    fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud;
    sensorCloud.time_stamp = 1.234;
    sensorCloud.point_cloud->width = 101;
    sensorCloud.point_cloud->height = 1;
    sensorCloud.point_cloud->is_dense = false;
    sensorCloud.point_cloud->points.resize(101);
    for (uint32_t y = 0; y < 10; ++y) {
        for (uint32_t x = 0; x < 10; ++x) {
            auto& point = sensorCloud.point_cloud->points[y * 10 + x];
            point.x = x * 0.035f;
            point.y = y * 0.035f;
            point.z = 1.0f;
        }
    }
    sensorCloud.point_cloud->points.back().x = 10.0f;
    sensorCloud.point_cloud->points.back().y = 10.0f;
    sensorCloud.point_cloud->points.back().z = 1.0f;

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr clean_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    std::vector<int> valid_indices;
    pcl::removeNaNFromPointCloud(*sensorCloud.point_cloud, *clean_cloud, valid_indices);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr downsampled_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::VoxelGrid<pcl::PointXYZRGB> voxel_filter;
    voxel_filter.setInputCloud(clean_cloud);
    voxel_filter.setLeafSize(0.035f, 0.035f, 0.035f);
    voxel_filter.filter(*downsampled_cloud);
    pcl::PointCloud<pcl::PointXYZRGB> expected_cloud;
    pcl::RadiusOutlierRemoval<pcl::PointXYZRGB> reference_filter;
    reference_filter.setInputCloud(downsampled_cloud);
    reference_filter.setRadiusSearch(0.05);
    reference_filter.setMinNeighborsInRadius(2);
    reference_filter.filter(expected_cloud);

    const auto actual_cloud = SUT.reduceNoise(sensorCloud);
    ASSERT_NE(actual_cloud.point_cloud, nullptr);
    EXPECT_LT(expected_cloud.size(), downsampled_cloud->size());
    EXPECT_LT(actual_cloud.point_cloud->size(), downsampled_cloud->size());
    ASSERT_EQ(actual_cloud.point_cloud->size(), expected_cloud.size());
    for (std::size_t i = 0; i < expected_cloud.size(); ++i) {
        EXPECT_FLOAT_EQ(actual_cloud.point_cloud->points[i].x, expected_cloud.points[i].x);
        EXPECT_FLOAT_EQ(actual_cloud.point_cloud->points[i].y, expected_cloud.points[i].y);
        EXPECT_FLOAT_EQ(actual_cloud.point_cloud->points[i].z, expected_cloud.points[i].z);
    }
}
TEST(DepthCameraNoiseReducerTests, BenchmarkFilterPerformance) {
    NoiseReducer SUT;
    ASSERT_TRUE(SUT.init());

    constexpr uint32_t benchmark_point_count = 307200;
    constexpr uint32_t benchmark_width = 640;
    constexpr uint32_t benchmark_height = 480;
    fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud = createTestRgbdMessage(benchmark_point_count);
    sensorCloud.time_stamp = 1.234;
    ASSERT_EQ(sensorCloud.point_cloud->size(), benchmark_point_count);
    ASSERT_EQ(sensorCloud.point_cloud->width, benchmark_width);
    ASSERT_EQ(sensorCloud.point_cloud->height, benchmark_height);

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr clean_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    std::vector<int> valid_indices;
    pcl::removeNaNFromPointCloud(*sensorCloud.point_cloud, *clean_cloud, valid_indices);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr voxelized_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::VoxelGrid<pcl::PointXYZRGB> voxel_filter;
    voxel_filter.setInputCloud(clean_cloud);
    voxel_filter.setLeafSize(0.035f, 0.035f, 0.035f);
    voxel_filter.filter(*voxelized_cloud);

    constexpr int warmup_iterations = 2;
    constexpr int measured_iterations = 20;
    constexpr double max_average_duration_ms = 500.0;
    constexpr double ideal_average_duration_ms = 100.0;
    std::vector<double> durations_ms;
    durations_ms.reserve(measured_iterations);
    std::size_t output_point_count = 0;

    std::cout << "\n======================================================\n";
    std::cout << "STARTING NOISE REDUCER BENCHMARK (" << measured_iterations << " MEASURED ITERATIONS)\n";
    std::cout << "======================================================\n";

    for (int i = 0; i < warmup_iterations + measured_iterations; ++i) {
        auto t_start = std::chrono::high_resolution_clock::now();
        auto cloud = SUT.reduceNoise(sensorCloud);
        auto t_end = std::chrono::high_resolution_clock::now();
        const double duration_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

        if (i == 0) {
            ASSERT_NE(cloud.point_cloud, nullptr);
            ASSERT_FLOAT_EQ(cloud.time_stamp, sensorCloud.time_stamp);
            ASSERT_FALSE(cloud.point_cloud->empty());
            EXPECT_TRUE(cloud.point_cloud->is_dense);
            output_point_count = cloud.point_cloud->size();
            EXPECT_LT(output_point_count, voxelized_cloud->size())
                << "Radius filtering must reject isolated synthetic depth spikes.";
        }
        if (i >= warmup_iterations)
            durations_ms.push_back(duration_ms);
    }
    ASSERT_EQ(sensorCloud.point_cloud->size(), benchmark_point_count);

    const auto [min_duration, max_duration] = std::minmax_element(durations_ms.begin(), durations_ms.end());
    const double total_duration_ms = std::accumulate(durations_ms.begin(), durations_ms.end(), 0.0);
    const double average_duration = total_duration_ms / measured_iterations;
    double estimated_hz = 1000.0 / average_duration;

    std::cout << "BENCHMARK RESULTS:\n";
    std::cout << " -> Input Points: " << sensorCloud.point_cloud->size() << " (" << benchmark_width << "x"
              << benchmark_height << ")\n";
    std::cout << " -> Min Latency: " << *min_duration << " ms\n";
    std::cout << " -> Max Latency: " << *max_duration << " ms\n";
    std::cout << " -> Avg Latency: " << average_duration << " ms\n";
    std::cout << " -> Estimated Throughput: " << estimated_hz << " Hz\n";
    std::cout << " -> Points after voxelization: " << voxelized_cloud->size() << "\n";
    std::cout << " -> Output Points: " << output_point_count << "\n";
    std::cout << " -> Average latency requirement: <= " << max_average_duration_ms << " ms\n";
    std::cout << " -> Ideal average latency: <= " << ideal_average_duration_ms << " ms\n";
    std::cout << "======================================================\n\n";

    EXPECT_LE(average_duration, max_average_duration_ms)
        << "Noise reduction average exceeds the 500 ms per-frame requirement.";
}