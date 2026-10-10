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

            // ==========================================================
            pcl::PointCloud<pcl::PointXYZRGB>::Ptr cleanCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
            std::vector<int> nan_indices;
            pcl::removeNaNFromPointCloud(*pclCloud, *cleanCloud, nan_indices);

            if (cleanCloud->empty()) {
                fast::rf::Logger::logWarn("Cloud only contained NaNs. Skipping filter.");
                return overlapRemovedPointCloud;
            }

            // ==========================================================
            // FIX 2: Wrap the filter in a try-catch to isolate PCL exceptions
            // ==========================================================
            try {
                pcl::RadiusOutlierRemoval<pcl::PointXYZRGB> ror;
                ror.setInputCloud(cleanCloud);  // Use the NaN-free cloud
                ror.setRadiusSearch(0.03);
                ror.setMinNeighborsInRadius(15);
                ror.filter(*pclCloudFiltered);

                std::size_t filteredOutCount = pclCloud->size() - pclCloudFiltered->size();
                double percentRemoved = 100.0 * (double)filteredOutCount / ((double)pclCloud->size());
                fast::rf::Logger::logWarn("Filtered Out: " + std::to_string(filteredOutCount) +
                                          " Perc: " + std::to_string(percentRemoved));
            } catch (const std::exception& e) {
                fast::rf::Logger::logError("PCL Filter threw an exception: " + std::string(e.what()));
                pclCloudFiltered = pclCloud;  // Fallback to raw cloud on failure instead of crashing
            }
        } else {
            pclCloudFiltered = pclCloud;
        }

        convertFromPCL<pcl::PointXYZRGB>(pclCloudFiltered, noiseRemovedPointCloud);

        return noiseRemovedPointCloud;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser