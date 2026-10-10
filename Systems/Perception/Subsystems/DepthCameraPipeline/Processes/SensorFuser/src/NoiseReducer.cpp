#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/voxel_grid.h>

#include <Infrastructure/Logger.hpp>
#include <NoiseReducer.hpp>
#include <chrono>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    bool NoiseReducer::init() { return true; }
    fast::rf::messages::SensorMsgs::PointCloudMsg NoiseReducer::reduceNoise(
        const fast::rf::messages::SensorMsgs::PointCloudMsg& overlapRemovedPointCloud) {
        // Start master stopwatch
        auto t_start = std::chrono::high_resolution_clock::now();

        fast::rf::messages::SensorMsgs::PointCloudMsg noiseRemovedPointCloud;
        noiseRemovedPointCloud.time_stamp = overlapRemovedPointCloud.time_stamp;
        bool noiseFilterEnable = true;

        if (!overlapRemovedPointCloud.point_cloud) {
            fast::rf::Logger::logError("PointCloudMsg contains a null PCL point cloud.");
            return noiseRemovedPointCloud;
        }
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr pclCloud = overlapRemovedPointCloud.point_cloud;

        pcl::PointCloud<pcl::PointXYZRGB>::Ptr pclCloudFiltered(new pcl::PointCloud<pcl::PointXYZRGB>);

        // Track intermediate timing steps
        long long ms_nan = 0;
        long long ms_voxel = 0;
        long long ms_filter = 0;

        if (noiseFilterEnable == true) {
            if (pclCloud->empty()) {
                return overlapRemovedPointCloud;
            }

            // =================================================================
            // TIME STAGE 1: Fast NaN Removal
            // =================================================================
            auto t_nan_start = std::chrono::high_resolution_clock::now();
            pcl::PointCloud<pcl::PointXYZRGB>::Ptr cleanCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
            std::vector<int> nan_indices;
            pcl::removeNaNFromPointCloud(*pclCloud, *cleanCloud, nan_indices);
            auto t_nan_end = std::chrono::high_resolution_clock::now();
            ms_nan = std::chrono::duration_cast<std::chrono::milliseconds>(t_nan_end - t_nan_start).count();

            if (cleanCloud->empty())
                return overlapRemovedPointCloud;

            // =================================================================
            // TIME STAGE 2: Voxel Grid Downsampling
            // =================================================================
            auto t_voxel_start = std::chrono::high_resolution_clock::now();
            pcl::PointCloud<pcl::PointXYZRGB>::Ptr downsampledCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
            pcl::VoxelGrid<pcl::PointXYZRGB> vg;
            vg.setInputCloud(cleanCloud);

            // INCREASE LEAF SIZE: Moving from 2cm to 3.5cm cuts the point count
            // quadratically, which drops filtering time exponentially.
            double voxelSize = 0.035f;
            vg.setLeafSize(voxelSize, voxelSize, voxelSize);
            vg.filter(*downsampledCloud);
            auto t_voxel_end = std::chrono::high_resolution_clock::now();
            ms_voxel = std::chrono::duration_cast<std::chrono::milliseconds>(t_voxel_end - t_voxel_start).count();

            if (downsampledCloud->empty())
                return overlapRemovedPointCloud;

            // =================================================================
            // TIME STAGE 3: Radius Outlier Removal Filter
            // =================================================================
            auto t_filter_start = std::chrono::high_resolution_clock::now();
            try {
                pcl::RadiusOutlierRemoval<pcl::PointXYZRGB> ror;
                ror.setInputCloud(downsampledCloud);

                // REMOVED: ror.setSearchMethod(tree) has been deleted.
                // This lets PCL manage its internal internal index layout automatically.

                // Geometric alignment parameters for 3.5cm voxels
                ror.setRadiusSearch(0.05);       // 5cm search window
                ror.setMinNeighborsInRadius(2);  // Clear floating artifacts safely

                ror.filter(*pclCloudFiltered);

                std::size_t filteredOutCount = pclCloud->size() - pclCloudFiltered->size();
                double percentRemoved = 100.0 * (double)filteredOutCount / ((double)pclCloud->size());
                fast::rf::Logger::logWarn("Start Size: " + std::to_string(pclCloud->size()) +
                                          " Filtered Out: " + std::to_string(filteredOutCount) +
                                          " Perc: " + std::to_string(percentRemoved));
            } catch (const std::exception& e) {
                fast::rf::Logger::logError("PCL Filter threw an exception: " + std::string(e.what()));
                pclCloudFiltered = pclCloud;
            }
            auto t_filter_end = std::chrono::high_resolution_clock::now();
            ms_filter = std::chrono::duration_cast<std::chrono::milliseconds>(t_filter_end - t_filter_start).count();
        } else {
            pclCloudFiltered = pclCloud;
        }

        noiseRemovedPointCloud.point_cloud = pclCloudFiltered;

        // Calculate remaining durations
        auto t_end = std::chrono::high_resolution_clock::now();
        auto ms_total = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();

        fast::rf::Logger::logWarn(
            "PERF BREAKDOWN -> "
            "NaN_Rem: " +
            std::to_string(ms_nan) +
            "ms | "
            "Voxel: " +
            std::to_string(ms_voxel) +
            "ms | "
            "RadFilter: " +
            std::to_string(ms_filter) +
            "ms || "
            "Total: " +
            std::to_string(ms_total) + "ms");

        return noiseRemovedPointCloud;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser