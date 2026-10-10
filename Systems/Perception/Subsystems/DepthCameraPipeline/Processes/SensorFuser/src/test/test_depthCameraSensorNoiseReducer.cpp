
#include <gtest/gtest.h>
#include <stdio.h>

#include <Infrastructure/Logger.hpp>
#include <NoiseReducer.hpp>
#include <chrono>
#include <random>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser;

fast::rf::messages::SensorMsgs::PointCloudMsg createTestRgbdMessage(uint32_t num_points) {
    fast::rf::messages::SensorMsgs::PointCloudMsg msg;
    msg.time_stamp = 123456789.012;
    msg.point_cloud->height = 1;
    msg.point_cloud->width = num_points;
    msg.point_cloud->is_dense = false;
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
TEST(DepthCameraNoiseReducer, BasicTests) {
    NoiseReducer SUT;
    ASSERT_TRUE(SUT.init());
    fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud = createTestRgbdMessage(307200);
    sensorCloud.time_stamp = 1.234;
    auto cloud = SUT.reduceNoise(sensorCloud);
    ASSERT_FLOAT_EQ(cloud.time_stamp, sensorCloud.time_stamp);
}
TEST(DepthCameraNoiseReducerTests, BenchmarkFilterPerformance) {
    NoiseReducer SUT;
    ASSERT_TRUE(SUT.init());

    // 1. Generate a realistic test cloud (307,200 points matches a typical 640x480 frame)
    fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud = createTestRgbdMessage(307200);
    sensorCloud.time_stamp = 1.234;

    // 2. Setup benchmark tracking parameters
    const int iterations = 50;  // Run 50 times to get a stable statistical sample
    long long total_duration_ms = 0;
    long long min_duration_ms = std::numeric_limits<long long>::max();
    long long max_duration_ms = 0;

    std::cout << "\n======================================================\n";
    std::cout << "STARTING NOISE REDUCER BENCHMARK (" << iterations << " ITERATIONS)\n";
    std::cout << "======================================================\n";

    for (int i = 0; i < iterations; ++i) {
        fast::rf::Logger::logWarn("Starting Iteration: " + std::to_string(i) + "." + std::to_string(iterations));
        auto t_start = std::chrono::high_resolution_clock::now();

        // Run the system under test
        auto cloud = SUT.reduceNoise(sensorCloud);

        auto t_end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();

        // Accumulate statistics
        total_duration_ms += duration;
        if (duration < min_duration_ms)
            min_duration_ms = duration;
        if (duration > max_duration_ms)
            max_duration_ms = duration;

        // Sanity check an assertion on the first iteration so we don't spam the engine
        if (i == 0) {
            ASSERT_FLOAT_EQ(cloud.time_stamp, sensorCloud.time_stamp);
        }
    }

    // 3. Print out clean telemetry summary metrics
    double average_duration = static_cast<double>(total_duration_ms) / iterations;
    double estimated_hz = 1000.0 / average_duration;

    std::cout << "BENCHMARK RESULTS:\n";
    std::cout << " -> Min Latency: " << min_duration_ms << " ms\n";
    std::cout << " -> Max Latency: " << max_duration_ms << " ms\n";
    std::cout << " -> Avg Latency: " << average_duration << " ms\n";
    std::cout << " -> Estimated Throughput: " << estimated_hz << " Hz\n";
    std::cout << "======================================================\n\n";
}