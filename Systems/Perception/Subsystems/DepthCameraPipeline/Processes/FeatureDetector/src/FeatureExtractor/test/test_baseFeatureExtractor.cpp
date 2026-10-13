/**
 * @compare_tag Process-BaseSourceTest v0.1
 *
 */
#include <gtest/gtest.h>
#include <stdio.h>

#include <FeatureExtractor/BaseFeatureExtractor.hpp>
#include <FeatureExtractor/IFeatureExtractor.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector;
class TestFeatureExtractorInterface : public IFeatureExtractor {
   public:
    bool init() { return true; }
    bool update([[maybe_unused]] double currentTimeSec) { return false; }
};
TEST(TestFeatureExtractorInterface, InterfaceTests) {
    TestFeatureExtractorInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_FALSE(SUT.update(0.0));
}
class TestBaseFeatureExtractor : public BaseFeatureExtractor {
   public:
    bool init() { return true; }
    bool update([[maybe_unused]] double currentTimeSec) { return false; }
};
TEST(TestBaseFeatureExtractor, BasicAssertions) {
    TestBaseFeatureExtractor SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_FALSE(SUT.update(0.0));
}
