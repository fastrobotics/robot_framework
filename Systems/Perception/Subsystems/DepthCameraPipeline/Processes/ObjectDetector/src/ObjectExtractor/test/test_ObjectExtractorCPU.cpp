#include <gtest/gtest.h>
#include <stdio.h>

#include <FeatureExtractor/FeatureExtractorCPU.hpp>
#include <ObjectExtractor/ObjectExtractorCPU.hpp>
using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector;
#include <pcl/io/pcd_io.h>

#include <Infrastructure/Logger.hpp>
TEST(ObjectExtractorCPU, BasicTests) {
    ObjectExtractorCPU SUT;
    ASSERT_TRUE(SUT.init());
}
TEST(ObjectExtractorCPU, SmallCloudTests) {
    fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector::FeatureExtractorCPU featureExtractor;
    ASSERT_TRUE(featureExtractor.init());

    std::string dataFile = std::string(TEST_DATA_DIR) + "/test_cloud.pcd";
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr input_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(dataFile, *input_cloud) == -1) {
        fast::rf::Logger::logError("Failed to read file: " + dataFile);
        ASSERT_TRUE(false);
    }
    fast::rf::messages::SensorMsgs::PointCloudMsg pointCloud;
    pointCloud.point_cloud = input_cloud;
    auto featurePointCloudContainer = featureExtractor.extractFeatures(pointCloud);
    auto featurePointCloud = featurePointCloudContainer.cloud;
    ASSERT_TRUE(featurePointCloudContainer.wereFeaturesExtracted);
    ASSERT_GT(featurePointCloud.size(), 0);

    ObjectExtractorCPU SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.setConfig(3.0f, 50));
    auto objectList =
        SUT.extractObjects(featurePointCloud.point_cloud, featurePointCloud.normals, featurePointCloud.fpfh_features);
    ASSERT_GT(objectList.size(), 0);
    for (auto object : objectList) {
        fast::rf::Logger::logDebug(object.pretty());
    }
}