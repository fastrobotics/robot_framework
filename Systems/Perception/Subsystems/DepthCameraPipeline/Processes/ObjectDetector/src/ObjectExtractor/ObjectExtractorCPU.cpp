/**
 * @file ObjectExtractorCPU.cpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-19
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <pcl/common/centroid.h>
#include <pcl/common/common.h>
#include <pcl/features/moment_of_inertia_estimation.h>
#include <pcl/segmentation/region_growing.h>

#include <ObjectExtractor/ObjectExtractorCPU.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector {
    std::vector<fast::rf::messages::VisionMsgs::Detection3DMsg> ObjectExtractorCPU::extractObjects(
        fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud) {
        std::vector<fast::rf::messages::VisionMsgs::Detection3DMsg> detections;
        if (sensorCloud.isValidFeatureCloud() == false) {
            fast::rf::Logger::logWarn("Sensor Clouid was not extracted to Features!");
            return detections;
        }
        auto objectList = extractObjects(sensorCloud.point_cloud, sensorCloud.normals, sensorCloud.fpfh_features);
        for (auto object : objectList) {
            auto detection = BaseObjectExtractor::convert(sensorCloud.time_stamp, object);
            detections.push_back(detection);
        }
        return detections;
    }
    std::vector<IObjectExtractor::DiscoveredObject> ObjectExtractorCPU::extractObjects(
        const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud, const pcl::PointCloud<pcl::Normal>::Ptr& normals,
        const pcl::PointCloud<pcl::FPFHSignature33>::Ptr& fpfh_features) {
        std::vector<DiscoveredObject> objects;
        printf("xxx1\n");

        // 1. Configure and run Region Growing Segmentation
        pcl::RegionGrowing<pcl::PointXYZRGB, pcl::Normal> reg;
        reg.setMinClusterSize(m_minClusterSize);
        reg.setMaxClusterSize(1000000);
        reg.setInputCloud(cloud);
        reg.setInputNormals(normals);
        printf("xxx2\n");
        // Configure normal proximity thresholds
        reg.setNumberOfNeighbours(30);
        reg.setSmoothnessThreshold(m_clusterToleranceDeg * M_PI / 180.0);  // Degrees to Radians
        reg.setCurvatureThreshold(1.0);  // Allows handling of moderately irregular surfaces

        std::vector<pcl::PointIndices> clusters;
        reg.extract(clusters);

        std::cout << "[Info] Region growing segmented " << clusters.size() << " discrete objects.\n";

        // 2. Process each isolated cluster independently
        int object_counter = 0;
        for (const auto& indices : clusters) {
            // Extract cluster subset
            pcl::PointCloud<pcl::PointXYZRGB>::Ptr cluster_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
            for (const auto& index : indices.indices) {
                cluster_cloud->push_back((*cloud)[index]);
            }
            cluster_cloud->width = cluster_cloud->size();
            cluster_cloud->height = 1;
            cluster_cloud->is_dense = true;

            // Calculate the spatial 3D Centroid
            Eigen::Vector4f centroid;
            pcl::compute3DCentroid(*cluster_cloud, centroid);

            // Calculate Oriented Bounding Box (OBB) dimensions
            pcl::MomentOfInertiaEstimation<pcl::PointXYZRGB> feature_extractor;
            feature_extractor.setInputCloud(cluster_cloud);
            feature_extractor.compute();

            pcl::PointXYZRGB min_point_OBB, max_point_OBB;
            pcl::PointXYZRGB position;
            Eigen::Matrix3f rotational_matrix;

            feature_extractor.getOBB(min_point_OBB, max_point_OBB, position, rotational_matrix);
            Eigen::Vector3f dimensions(max_point_OBB.x - min_point_OBB.x, max_point_OBB.y - min_point_OBB.y,
                                       max_point_OBB.z - min_point_OBB.z);
            DiscoveredObject obj;
            if (fpfh_features->empty() == false) {
                // 3. Pool local features into a Global Object Descriptor
                // Averaging the histogram bins across all component points inside this instance
                Eigen::VectorXf global_descriptor = Eigen::VectorXf::Zero(33);
                for (const auto& index : indices.indices) {
                    const pcl::FPFHSignature33& point_fpfh = (*fpfh_features)[index];
                    for (int f = 0; f < 33; ++f) {
                        global_descriptor[f] += point_fpfh.histogram[f];
                    }
                }
                global_descriptor /= static_cast<float>(indices.indices.size());
                obj.global_fpfh = global_descriptor;
            }

            // 4. Populate object structure entry

            obj.id = object_counter++;
            obj.point_count = indices.indices.size();
            obj.centroid = centroid;
            obj.dimensions = dimensions;
            obj.rotation_matrix = rotational_matrix;
            obj.cloud_cluster = cluster_cloud;

            objects.push_back(obj);
        }

        return objects;
    }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector