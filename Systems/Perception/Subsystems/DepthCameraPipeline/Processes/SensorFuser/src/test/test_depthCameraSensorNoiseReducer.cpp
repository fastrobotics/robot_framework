
#include <gtest/gtest.h>
#include <pcl/filters/filter.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/voxel_grid.h>
#include <stdio.h>

#include <CPUNoiseReducer.hpp>
#include <NoiseReducer.hpp>
#ifdef ARCHITECTURE_JETSONNANO
#include <GPUNoiseReducer.hpp>
#endif
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
TEST(DepthCameraNoiseReducer, RejectsInvalidConfiguration) {
    NoiseReducer SUT;
    EXPECT_FALSE(SUT.setConfig(0.0, 0.05, 2));
    EXPECT_FALSE(SUT.setConfig(0.035, std::numeric_limits<double>::infinity(), 2));
    EXPECT_FALSE(SUT.setConfig(std::numeric_limits<double>::max(), 0.05, 2));
    EXPECT_FALSE(SUT.setConfig(0.035, 0.05, std::numeric_limits<uint64_t>::max()));
    EXPECT_TRUE(SUT.setConfig(0.035, 0.05, 2));
}
TEST(DepthCameraNoiseReducer, EmptyAndNullInputsPreserveTimestamp) {
    NoiseReducer SUT;
    ASSERT_TRUE(SUT.init());

    fast::rf::messages::SensorMsgs::PointCloudMsg empty_input;
    empty_input.time_stamp = 4.25;
    const auto empty_output = SUT.reduceNoise(empty_input);
    EXPECT_EQ(empty_output.time_stamp, empty_input.time_stamp);
    EXPECT_EQ(empty_output.point_cloud, empty_input.point_cloud);

    fast::rf::messages::SensorMsgs::PointCloudMsg null_input;
    null_input.time_stamp = 7.5;
    null_input.point_cloud.reset();
    const auto null_output = SUT.reduceNoise(null_input);
    ASSERT_NE(null_output.point_cloud, nullptr);
    EXPECT_TRUE(null_output.point_cloud->empty());
    EXPECT_TRUE(null_output.point_cloud->is_dense);
    EXPECT_EQ(null_output.time_stamp, null_input.time_stamp);
}
TEST(DepthCameraNoiseReducer, AllInvalidInputProducesEmptyDenseOutput) {
    CPUNoiseReducer cpu_backend;
    ASSERT_TRUE(cpu_backend.init());
    fast::rf::messages::SensorMsgs::PointCloudMsg input;
    input.time_stamp = 9.75;
    input.point_cloud->width = 2;
    input.point_cloud->height = 1;
    input.point_cloud->is_dense = false;
    input.point_cloud->points.resize(2);
    for (auto& point : input.point_cloud->points) point.x = std::numeric_limits<float>::quiet_NaN();

    const auto output = cpu_backend.reduceNoise(input);
    ASSERT_NE(output.point_cloud, nullptr);
    EXPECT_TRUE(output.point_cloud->empty());
    EXPECT_TRUE(output.point_cloud->is_dense);
    EXPECT_EQ(output.point_cloud->width, 0);
    EXPECT_EQ(output.point_cloud->height, 1);
    EXPECT_EQ(output.time_stamp, input.time_stamp);
}
TEST(DepthCameraNoiseReducer, ParallelRadiusFilterMatchesPcl) {
    CPUNoiseReducer SUT;
    ASSERT_TRUE(SUT.init());

    fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud;
    sensorCloud.time_stamp = 1.234;
    sensorCloud.point_cloud->header.frame_id = "camera";
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
            point.r = static_cast<uint8_t>(y * 10 + x);
            point.g = static_cast<uint8_t>(y * 10 + x + 1);
            point.b = static_cast<uint8_t>(y * 10 + x + 2);
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
    EXPECT_EQ(actual_cloud.point_cloud->header.frame_id, sensorCloud.point_cloud->header.frame_id);
    EXPECT_LT(expected_cloud.size(), downsampled_cloud->size());
    EXPECT_LT(actual_cloud.point_cloud->size(), downsampled_cloud->size());
    ASSERT_EQ(actual_cloud.point_cloud->size(), expected_cloud.size());
    for (std::size_t i = 0; i < expected_cloud.size(); ++i) {
        EXPECT_FLOAT_EQ(actual_cloud.point_cloud->points[i].x, expected_cloud.points[i].x);
        EXPECT_FLOAT_EQ(actual_cloud.point_cloud->points[i].y, expected_cloud.points[i].y);
        EXPECT_FLOAT_EQ(actual_cloud.point_cloud->points[i].z, expected_cloud.points[i].z);
        EXPECT_EQ(actual_cloud.point_cloud->points[i].r, expected_cloud.points[i].r);
        EXPECT_EQ(actual_cloud.point_cloud->points[i].g, expected_cloud.points[i].g);
        EXPECT_EQ(actual_cloud.point_cloud->points[i].b, expected_cloud.points[i].b);
    }
}
#ifdef ARCHITECTURE_JETSONNANO
TEST(DepthCameraNoiseReducer, GpuBackendMatchesCpuBackend) {
    if (!GPUNoiseReducer::isAvailable())
        GTEST_SKIP() << "No usable CUDA device is available.";

    fast::rf::messages::SensorMsgs::PointCloudMsg input;
    input.time_stamp = 2.468;
    input.point_cloud->header.frame_id = "camera";
    input.point_cloud->width = 101;
    input.point_cloud->height = 1;
    input.point_cloud->is_dense = true;
    input.point_cloud->points.resize(101);
    for (uint32_t y = 0; y < 10; ++y) {
        for (uint32_t x = 0; x < 10; ++x) {
            auto& point = input.point_cloud->points[y * 10 + x];
            point.x = x * 0.035f;
            point.y = y * 0.035f;
            point.z = 1.0f;
            point.r = static_cast<uint8_t>(y * 10 + x);
            point.g = static_cast<uint8_t>(y * 10 + x + 1);
            point.b = static_cast<uint8_t>(y * 10 + x + 2);
        }
    }
    input.point_cloud->points.back().x = 10.0f;
    input.point_cloud->points.back().y = 10.0f;
    input.point_cloud->points.back().z = 1.0f;

    CPUNoiseReducer cpu_backend;
    GPUNoiseReducer gpu_backend;
    ASSERT_TRUE(cpu_backend.init());
    ASSERT_TRUE(gpu_backend.init());
    const auto cpu_output = cpu_backend.reduceNoise(input);
    const auto gpu_output = gpu_backend.reduceNoise(input);
    ASSERT_EQ(gpu_output.point_cloud->size(), cpu_output.point_cloud->size());
    EXPECT_EQ(gpu_output.time_stamp, cpu_output.time_stamp);
    EXPECT_EQ(gpu_output.point_cloud->header.frame_id, cpu_output.point_cloud->header.frame_id);
    for (std::size_t i = 0; i < cpu_output.point_cloud->size(); ++i) {
        const auto& cpu_point = cpu_output.point_cloud->points[i];
        const auto& gpu_point = gpu_output.point_cloud->points[i];
        EXPECT_FLOAT_EQ(gpu_point.x, cpu_point.x);
        EXPECT_FLOAT_EQ(gpu_point.y, cpu_point.y);
        EXPECT_FLOAT_EQ(gpu_point.z, cpu_point.z);
        EXPECT_EQ(gpu_point.r, cpu_point.r);
        EXPECT_EQ(gpu_point.g, cpu_point.g);
        EXPECT_EQ(gpu_point.b, cpu_point.b);
    }
}
#endif
TEST(DepthCameraNoiseReducerTests, BenchmarkFilterPerformance) {
    CPUNoiseReducer cpu_backend;
    NoiseReducer automatic_backend;
    ASSERT_TRUE(cpu_backend.init());
    ASSERT_TRUE(automatic_backend.init());

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
    std::vector<double> cpu_durations_ms;
    std::vector<double> automatic_durations_ms;
    cpu_durations_ms.reserve(measured_iterations);
    automatic_durations_ms.reserve(measured_iterations);
    std::size_t cpu_output_point_count = 0;
    std::size_t automatic_output_point_count = 0;

    std::cout << "\n======================================================\n";
    std::cout << "STARTING NOISE REDUCER BENCHMARK (" << measured_iterations << " MEASURED ITERATIONS)\n";
    std::cout << "======================================================\n";

    for (int i = 0; i < warmup_iterations + measured_iterations; ++i) {
        auto cpu_start = std::chrono::high_resolution_clock::now();
        auto cpu_cloud = cpu_backend.reduceNoise(sensorCloud);
        auto cpu_end = std::chrono::high_resolution_clock::now();
        const double cpu_duration_ms = std::chrono::duration<double, std::milli>(cpu_end - cpu_start).count();

        auto automatic_start = std::chrono::high_resolution_clock::now();
        auto automatic_cloud = automatic_backend.reduceNoise(sensorCloud);
        auto automatic_end = std::chrono::high_resolution_clock::now();
        const double automatic_duration_ms =
            std::chrono::duration<double, std::milli>(automatic_end - automatic_start).count();

        if (i == 0) {
            ASSERT_NE(cpu_cloud.point_cloud, nullptr);
            ASSERT_NE(automatic_cloud.point_cloud, nullptr);
            ASSERT_FLOAT_EQ(cpu_cloud.time_stamp, sensorCloud.time_stamp);
            ASSERT_FLOAT_EQ(automatic_cloud.time_stamp, sensorCloud.time_stamp);
            ASSERT_FALSE(cpu_cloud.point_cloud->empty());
            ASSERT_FALSE(automatic_cloud.point_cloud->empty());
            EXPECT_TRUE(cpu_cloud.point_cloud->is_dense);
            EXPECT_TRUE(automatic_cloud.point_cloud->is_dense);
            cpu_output_point_count = cpu_cloud.point_cloud->size();
            automatic_output_point_count = automatic_cloud.point_cloud->size();
            EXPECT_LT(cpu_output_point_count, voxelized_cloud->size())
                << "CPU radius filtering must reject isolated synthetic depth spikes.";
            EXPECT_LT(automatic_output_point_count, voxelized_cloud->size())
                << "Radius filtering must reject isolated synthetic depth spikes.";
            ASSERT_EQ(cpu_output_point_count, automatic_output_point_count);
        }
        if (i >= warmup_iterations) {
            cpu_durations_ms.push_back(cpu_duration_ms);
            automatic_durations_ms.push_back(automatic_duration_ms);
        }
    }
    ASSERT_EQ(sensorCloud.point_cloud->size(), benchmark_point_count);

    struct LatencySummary {
        double average;
        double median;
        double p95;
        double maximum;
    };
    const auto summarize = [](std::vector<double> samples) {
        std::sort(samples.begin(), samples.end());
        const double average = std::accumulate(samples.begin(), samples.end(), 0.0) / samples.size();
        const std::size_t middle = samples.size() / 2;
        const double median = samples.size() % 2 == 0 ? (samples[middle - 1] + samples[middle]) / 2.0 : samples[middle];
        const std::size_t p95_index = static_cast<std::size_t>(std::ceil(0.95 * samples.size())) - 1;
        return LatencySummary{average, median, samples[p95_index], samples.back()};
    };
    const auto cpu_latency = summarize(cpu_durations_ms);
    const auto automatic_latency = summarize(automatic_durations_ms);

    std::cout << "BENCHMARK RESULTS:\n";
    std::cout << " -> Input Points: " << sensorCloud.point_cloud->size() << " (" << benchmark_width << "x"
              << benchmark_height << ")\n";
    std::cout << " -> CPU Avg / Median / P95 / Max Latency: " << cpu_latency.average << " / " << cpu_latency.median
              << " / " << cpu_latency.p95 << " / " << cpu_latency.maximum << " ms\n";
    std::cout << " -> Automatic Avg / Median / P95 / Max Latency: " << automatic_latency.average << " / "
              << automatic_latency.median << " / " << automatic_latency.p95 << " / " << automatic_latency.maximum
              << " ms\n";
    std::cout << " -> Automatic Estimated Throughput: " << 1000.0 / automatic_latency.average << " Hz\n";
    std::cout << " -> Points after voxelization: " << voxelized_cloud->size() << "\n";
    std::cout << " -> CPU Output Points: " << cpu_output_point_count << "\n";
    std::cout << " -> Automatic Output Points: " << automatic_output_point_count << "\n";
    std::cout << " -> Average latency requirement: <= " << max_average_duration_ms << " ms\n";
    std::cout << " -> Ideal average latency: <= " << ideal_average_duration_ms << " ms\n";
    std::cout << "======================================================\n\n";

    EXPECT_LE(cpu_latency.average, max_average_duration_ms)
        << "CPU noise reduction average exceeds the 500 ms per-frame requirement.";
    EXPECT_LE(automatic_latency.average, max_average_duration_ms)
        << "Automatically selected noise reduction average exceeds the 500 ms per-frame requirement.";
}