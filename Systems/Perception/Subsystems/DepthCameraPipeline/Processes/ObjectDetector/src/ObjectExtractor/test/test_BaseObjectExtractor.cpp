#include <gtest/gtest.h>
#include <stdio.h>

#include <Eigen/Dense>
#include <ObjectExtractor/BaseObjectExtractor.hpp>
#include <PointCloudMsg.hpp>
using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector;

#include <Infrastructure/Logger.hpp>
class TestBaseObjectExtractor : public BaseObjectExtractor {
   public:
    std::vector<fast::rf::messages::VisionMsgs::Detection3DMsg> extractObjects(
        [[maybe_unused]] fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud) override {
        std::vector<fast::rf::messages::VisionMsgs::Detection3DMsg> detections;
        return detections;
    }

   protected:
   private:
    std::vector<DiscoveredObject> extractObjects(
        [[maybe_unused]] const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud,
        [[maybe_unused]] const pcl::PointCloud<pcl::Normal>::Ptr& normals,
        [[maybe_unused]] const pcl::PointCloud<pcl::FPFHSignature33>::Ptr& fpfh_features) override {
        std::vector<DiscoveredObject> objects;
        return objects;
    }
};
TEST(TestBaseObjectExtractor, ConversionTests) {
    TestBaseObjectExtractor SUT;
    ASSERT_TRUE(SUT.init());
    {  // Simple Object
        auto cloud = fast::rf::messages::SensorMsgs::PointCloudMsg::generateRGBCloud(10);
        cloud.time_stamp = 1.234;
        IObjectExtractor::DiscoveredObject object;
        object.id = 123;
        object.centroid.x() = 1.0;
        object.centroid.y() = 2.0;
        object.centroid.z() = 3.0;
        object.dimensions.x() = 4.0;
        object.dimensions.y() = 5.0;
        object.dimensions.z() = 6.0;
        float expected_roll = 15.0f * M_PI / 180.0f;
        float expected_pitch = -25.0f * M_PI / 180.0f;
        float expected_yaw = 45.0f * M_PI / 180.0f;
        Eigen::Matrix3f rot_x = Eigen::AngleAxisf(expected_roll, Eigen::Vector3f::UnitX()).toRotationMatrix();
        Eigen::Matrix3f rot_y = Eigen::AngleAxisf(expected_pitch, Eigen::Vector3f::UnitY()).toRotationMatrix();
        Eigen::Matrix3f rot_z = Eigen::AngleAxisf(expected_yaw, Eigen::Vector3f::UnitZ()).toRotationMatrix();
        object.rotation_matrix = rot_x * rot_y * rot_z;

        object.cloud_cluster = cloud.point_cloud;
        auto detection = SUT.convert(cloud.time_stamp, object);
        ASSERT_FLOAT_EQ(detection.time_stamp, cloud.time_stamp);
        ASSERT_GT(detection.results.size(), 0);
        ASSERT_EQ(detection.results.size(), 1);
        auto result = detection.results[0];

        ASSERT_FLOAT_EQ(result.pose.pose.position.x, object.centroid.x());
        ASSERT_FLOAT_EQ(result.pose.pose.position.y, object.centroid.y());
        ASSERT_FLOAT_EQ(result.pose.pose.position.z, object.centroid.z());
        ASSERT_FLOAT_EQ(result.pose.pose.orientation.roll, expected_roll);
        ASSERT_FLOAT_EQ(result.pose.pose.orientation.pitch, expected_pitch);
        ASSERT_FLOAT_EQ(result.pose.pose.orientation.yaw, expected_yaw);

        ASSERT_GT(detection.source_cloud.size(), 0);
        ASSERT_EQ(detection.source_cloud.size(), cloud.size());
        ASSERT_FLOAT_EQ(detection.bbox.center.position.x, object.centroid.x());
        ASSERT_FLOAT_EQ(detection.bbox.center.position.y, object.centroid.y());
        ASSERT_FLOAT_EQ(detection.bbox.center.position.z, object.centroid.z());
        ASSERT_FLOAT_EQ(detection.bbox.size.x, object.dimensions.x());
        ASSERT_FLOAT_EQ(detection.bbox.size.y, object.dimensions.y());
        ASSERT_FLOAT_EQ(detection.bbox.size.z, object.dimensions.z());

        fast::rf::Logger::logInfo(detection.pretty());
    }
}