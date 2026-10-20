/**
 * @compare_tag Process-SourceTest v0.1
 *
 */

#include <gtest/gtest.h>
#include <pcl/io/pcd_io.h>
#include <stdio.h>

#include <FeatureExtractor/FeatureExtractorCPU.hpp>
#include <ObjectDetectorProcess.hpp>
using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector;
#include <Infrastructure/Logger.hpp>

TEST(ObjectDetectorProcess, Tests) {
    ObjectDetectorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
    auto diagnostics = SUT.getDiagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    for (auto diagnostic : diagnostics) {
        ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
    fast::rf::Logger::logDebug(SUT.pretty());
}
TEST(ObjectDetectorProcess, ConversionTests) {
    ObjectDetectorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);
}
TEST(ObjectDetectorProcess, DetectObjects) {
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

    ObjectDetectorProcess SUT;
    ASSERT_TRUE(SUT.init());
    auto detections = SUT.detectObjects(featurePointCloud);
    ASSERT_GT(detections.size(), 0);
}