
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
