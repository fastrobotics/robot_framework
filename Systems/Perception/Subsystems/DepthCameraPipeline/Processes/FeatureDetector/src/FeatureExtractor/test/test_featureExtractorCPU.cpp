
#include <gtest/gtest.h>
#include <stdio.h>

#include <FeatureExtractor/FeatureExtractorCPU.hpp>
#include <FeatureExtractor/IFeatureExtractor.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector;

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
TEST(FeatureExtractorCPU, BasicAssertions) {
    FeatureExtractorCPU SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
}
TEST(FeatureExtractorCPU, TestOperation) {
    FeatureExtractorCPU SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
    fast::rf::messages::SensorMsgs::PointCloudMsg pointCloud = createTestRgbdMessage(1.0, 640, 480);
    auto output = SUT.extractFeatures(pointCloud);
    ASSERT_TRUE(output.cloud.isValidFeatureCloud());
    ASSERT_TRUE(output.wereFeaturesExtracted);
}
