/**
 * @file BaseFeatureExtractor.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-13
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <pcl/features/fpfh.h>
#include <pcl/features/normal_3d.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/search/kdtree.h>

#include <FeatureExtractor/IFeatureExtractor.hpp>
#include <Infrastructure/Logger.hpp>
#include <memory>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector {
    using PointCloudXYZRGB = pcl::PointCloud<pcl::PointXYZRGB>;
    using PointCloudNormal = pcl::PointCloud<pcl::Normal>;
    using PointCloudFPFH = pcl::PointCloud<pcl::FPFHSignature33>;
    class BaseFeatureExtractor : public IFeatureExtractor {
       public:
        bool init();
        // bool setConfig(bool)
        bool update(double currentTimeSec);

       protected:
        std::string pretty();
        double m_normalRadius_m{0.0};
        double m_fphRadius_m{0.0};
        struct {
            float x{0.0f}, y{0.0f}, z{0.0f};
        } m_viewpoint;
        uint64_t m_extractedCount{0};
        PointCloudNormal::Ptr m_normals{std::make_shared<PointCloudNormal>()};
        PointCloudFPFH::Ptr m_fpfhFeatures{std::make_shared<PointCloudFPFH>()};
        bool m_enableFPHFFeatureExtraction{false};
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector