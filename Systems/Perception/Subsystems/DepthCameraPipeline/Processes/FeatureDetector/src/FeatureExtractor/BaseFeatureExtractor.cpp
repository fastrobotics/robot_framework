#include <FeatureExtractor/BaseFeatureExtractor.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector {
    std::string BaseFeatureExtractor::pretty() {
        std::string str = "Base Feature Extractor\n";
        str += "\tExtracted Point Clouds: " + std::to_string(m_extractedCount) + "\n";
        str += "\tNormal Radius: " + std::to_string(m_normalRadius_m) + "\n";
        str += "\tFPH Radius: " + std::to_string(m_fphRadius_m) + "\n";
        return str;
    }
    bool BaseFeatureExtractor::init() {
        m_normalRadius_m = 0.03f;
        m_fphRadius_m = 0.05f;
        return true;
    }
    bool BaseFeatureExtractor::update([[maybe_unused]] double currentTimeSec) { return true; }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector
