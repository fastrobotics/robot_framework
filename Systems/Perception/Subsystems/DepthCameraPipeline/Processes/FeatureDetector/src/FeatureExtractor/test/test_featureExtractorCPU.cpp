
#include <gtest/gtest.h>
#include <stdio.h>

#include <FeatureExtractor/FeatureExtractorCPU.hpp>
#include <FeatureExtractor/IFeatureExtractor.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector;
TEST(FeatureExtractorCPU, BasicAssertions) {
    FeatureExtractorCPU SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
}
TEST(FeatureExtractorCPU, TestOperation) {
    FeatureExtractorCPU SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
    fast::rf::messages::SensorMsgs::PointCloudMsg pointCloud =
        fast::rf::messages::SensorMsgs::PointCloudMsg::generateRGBCloud(20);
    auto output = SUT.extractFeatures(pointCloud);
    ASSERT_TRUE(output.cloud.isValidFeatureCloud());
    ASSERT_TRUE(output.wereFeaturesExtracted);
}
