#include <pcl/filters/radius_outlier_removal.h>

#include <Infrastructure/Logger.hpp>
#include <NoiseReducer.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    bool NoiseReducer::init() { return true; }
    fast::rf::messages::SensorMsgs::PointCloudMsg NoiseReducer::reduceNoise(
        fast::rf::messages::SensorMsgs::PointCloudMsg overlapRemovedPointCloud) {
        fast::rf::messages::SensorMsgs::PointCloudMsg noiseRemovedPointCloud;
        bool noiseFilterEnable = true;

        pcl::PointCloud<pcl::PointXYZRGB>::Ptr pclCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
        convertToPCL<pcl::PointXYZRGB>(overlapRemovedPointCloud, pclCloud);
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr pclCloudFiltered(new pcl::PointCloud<pcl::PointXYZRGB>);
        if (noiseFilterEnable == true) {
            if (pclCloud->empty()) {
                return overlapRemovedPointCloud;
            }

            pcl::RadiusOutlierRemoval<pcl::PointXYZRGB> ror;
            ror.setInputCloud(pclCloud);
            ror.setRadiusSearch(0.03);        // 3cm search radius
            ror.setMinNeighborsInRadius(15);  // Reject points with fewer than 15 neighbors
            ror.filter(*pclCloudFiltered);
            std::size_t filteredOutCount = pclCloud->size() - pclCloudFiltered->size();
            double percentRemoved = 100.0 * (double)filteredOutCount / ((double)pclCloud->size());
            fast::rf::Logger::logWarn("Filtered Out: " + std::to_string(filteredOutCount) +
                                      " Perc: " + std::to_string(percentRemoved));
        } else {
            pclCloudFiltered = pclCloud;
        }

        convertFromPCL<pcl::PointXYZRGB>(pclCloudFiltered, noiseRemovedPointCloud);

        return noiseRemovedPointCloud;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser