#include <pcl/filters/statistical_outlier_removal.h>

#include <Infrastructure/Logger.hpp>
#include <NoiseReducer.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    bool NoiseReducer::init() { return true; }
    fast::rf::messages::SensorMsgs::PointCloudMsg NoiseReducer::reduceNoise(
        fast::rf::messages::SensorMsgs::PointCloudMsg overlapRemovedPointCloud) {
        fast::rf::messages::SensorMsgs::PointCloudMsg cloudMsg = overlapRemovedPointCloud;
        fast::rf::messages::SensorMsgs::PointCloudMsg noiseRemovedPointCloud;
        bool noiseFilterEnable = true;
        if (noiseFilterEnable == true) {
            pcl::PointCloud<pcl::PointXYZRGB>::Ptr pclCloud;
            convertToPCL<pcl::PointXYZRGB>(cloudMsg, pclCloud);
            if (pclCloud->empty()) {
                return overlapRemovedPointCloud;
            }
            pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> sor;
            sor.setInputCloud(pclCloud);

            // 2. Set the number of neighbors to analyze for each point (Default: 50)
            sor.setMeanK(50);

            // 3. Set the standard deviation multiplier threshold (Default: 1.0)
            // Points with a distance larger than (mean + 1.0 * stddev) are considered noise.
            // Lower values (e.g., 0.8) are more aggressive; higher values (e.g., 2.0) are more lenient.
            sor.setStddevMulThresh(1.0);

            // 4. Apply the filter
            pcl::PointCloud<pcl::PointXYZRGB>::Ptr pclCloudFiltered(new pcl::PointCloud<pcl::PointXYZRGB>);
            sor.filter(*pclCloudFiltered);

            convertFromPCL<pcl::PointXYZRGB>(pclCloudFiltered, noiseRemovedPointCloud);
        } else {
            noiseRemovedPointCloud = cloudMsg;
        }
        return noiseRemovedPointCloud;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser