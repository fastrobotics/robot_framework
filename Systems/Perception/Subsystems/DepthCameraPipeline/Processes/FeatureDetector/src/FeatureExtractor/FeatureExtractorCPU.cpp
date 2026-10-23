#include <FeatureExtractor/FeatureExtractorCPU.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector {
    bool FeatureExtractorCPU::init() {
        if (BaseFeatureExtractor::init() == false) {
            fast::rf::Logger::logError("Base Feature Extractor not able to Initialize!");
            return false;
        }
        return true;
    }
    bool FeatureExtractorCPU::update([[maybe_unused]] double currentTimeSec) {
        if (BaseFeatureExtractor::update(currentTimeSec) == false) {
            fast::rf::Logger::logWarn("Base Feature Extractor not able to Update!");
            return false;
        }
        return true;
    }
    std::string FeatureExtractorCPU::pretty() {
        std::string str = "--- Feature Extractor (CPU) ---\n";
        str += BaseFeatureExtractor::pretty();
        return str;
    }
    FeatureExtractionContainer FeatureExtractorCPU::extractFeatures(
        fast::rf::messages::SensorMsgs::PointCloudMsg pointCloud) {
        FeatureExtractionContainer container;
        container.cloud = pointCloud;
        std::size_t inputSize = container.cloud.size();
        auto tree = std::make_shared<pcl::search::KdTree<pcl::PointXYZRGB>>();
        pcl::NormalEstimation<pcl::PointXYZRGB, pcl::Normal> ne;
        ne.setInputCloud(pointCloud.point_cloud);
        ne.setSearchMethod(tree);
        ne.setRadiusSearch(m_normalRadius_m);
        ne.setViewPoint(m_viewpoint.x, m_viewpoint.y, m_viewpoint.z);
        m_normals->clear();
        ne.compute(*m_normals);
        if (m_enableFPHFFeatureExtraction) {
            pcl::FPFHEstimation<pcl::PointXYZRGB, pcl::Normal, pcl::FPFHSignature33> fpfh;
            fpfh.setInputCloud(pointCloud.point_cloud);
            fpfh.setInputNormals(m_normals);
            fpfh.setSearchMethod(tree);
            fpfh.setRadiusSearch(m_fphRadius_m);
            m_fpfhFeatures->clear();
            fpfh.compute(*m_fpfhFeatures);
            container.cloud.fpfh_features = m_fpfhFeatures;
        }
        container.cloud.normals = m_normals;
        container.wereFeaturesExtracted = container.cloud.isValidFeatureCloud();
        if (container.wereFeaturesExtracted) {
            m_extractedCount++;
        }
        std::size_t outputSize = container.cloud.size();
        double reductionRatioPerc = ((double)outputSize - (double)inputSize) / (double)inputSize * 100.0;
        fast::rf::Logger::logInfo("Reduction Ratio Perc: " + std::to_string(reductionRatioPerc) + " (%)");
        return container;
    }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector
