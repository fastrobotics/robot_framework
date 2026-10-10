#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/search/kdtree.h>

#include <Infrastructure/Logger.hpp>
#include <NoiseReducer.hpp>
#include <chrono>
#include <pcl/search/impl/kdtree.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    bool NoiseReducer::init() { return true; }
    fast::rf::messages::SensorMsgs::PointCloudMsg NoiseReducer::reduceNoise(
        const fast::rf::messages::SensorMsgs::PointCloudMsg& overlapRemovedPointCloud) {
        // Start master stopwatch
        auto t_start = std::chrono::high_resolution_clock::now();

        fast::rf::messages::SensorMsgs::PointCloudMsg noiseRemovedPointCloud;
        bool noiseFilterEnable = true;

        pcl::PointCloud<pcl::PointXYZRGB>::Ptr pclCloud(new pcl::PointCloud<pcl::PointXYZRGB>);

        // =================================================================
        // TIME STAGE 1: Input Conversion
        // =================================================================
        auto t_conv_in_start = std::chrono::high_resolution_clock::now();
        convertToPCL<pcl::PointXYZRGB>(overlapRemovedPointCloud, pclCloud);
        auto t_conv_in_end = std::chrono::high_resolution_clock::now();

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
            // TIME STAGE 2: Fast NaN Removal
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
            // TIME STAGE 3: Voxel Grid Downsampling
            // =================================================================
            auto t_voxel_start = std::chrono::high_resolution_clock::now();
            pcl::PointCloud<pcl::PointXYZRGB>::Ptr downsampledCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
            pcl::VoxelGrid<pcl::PointXYZRGB> vg;
            vg.setInputCloud(cleanCloud);
            double voxelSize = 0.02f;
            vg.setLeafSize(voxelSize, voxelSize, voxelSize);
            vg.filter(*downsampledCloud);
            auto t_voxel_end = std::chrono::high_resolution_clock::now();
            ms_voxel = std::chrono::duration_cast<std::chrono::milliseconds>(t_voxel_end - t_voxel_start).count();

            if (downsampledCloud->empty())
                return overlapRemovedPointCloud;

            // =================================================================
            // TIME STAGE 4: Radius Outlier Removal Filter
            // =================================================================
            auto t_filter_start = std::chrono::high_resolution_clock::now();
            try {
                pcl::RadiusOutlierRemoval<pcl::PointXYZRGB> ror;
                ror.setInputCloud(downsampledCloud);

                // FIX 1: Change to KdTreeFLANN for proper multi-threaded backend routing
                typename pcl::search::KdTreeFLANN<pcl::PointXYZRGB>::Ptr tree(
                    new pcl::search::KdTreeFLANN<pcl::PointXYZRGB>);
                ror.setSearchMethod(tree);

                // FIX 2: Tighten geometric limits relative to your 2cm (0.02f) voxels
                ror.setRadiusSearch(0.025);      // 2.5cm search radius window
                ror.setMinNeighborsInRadius(2);  // Require at least 2 adjacent neighbors

                ror.filter(*pclCloudFiltered);

                std::size_t filteredOutCount = pclCloud->size() - pclCloudFiltered->size();
                double percentRemoved = 100.0 * (double)filteredOutCount / ((double)pclCloud->size());
                fast::rf::Logger::logWarn("Filtered Out: " + std::to_string(filteredOutCount) +
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

        // =================================================================
        // TIME STAGE 5: Output Conversion
        // =================================================================
        auto t_conv_out_start = std::chrono::high_resolution_clock::now();
        convertFromPCL<pcl::PointXYZRGB>(pclCloudFiltered, noiseRemovedPointCloud);
        auto t_conv_out_end = std::chrono::high_resolution_clock::now();

        // Calculate remaining durations
        auto ms_in = std::chrono::duration_cast<std::chrono::milliseconds>(t_conv_in_end - t_conv_in_start).count();
        auto ms_out = std::chrono::duration_cast<std::chrono::milliseconds>(t_conv_out_end - t_conv_out_start).count();
        auto ms_total = std::chrono::duration_cast<std::chrono::milliseconds>(t_conv_out_end - t_start).count();

        // Print structural metrics breakdown
        fast::rf::Logger::logWarn(
            "PERF BREAKDOWN -> "
            "InConv: " +
            std::to_string(ms_in) +
            "ms | "
            "NaN_Rem: " +
            std::to_string(ms_nan) +
            "ms | "
            "Voxel: " +
            std::to_string(ms_voxel) +
            "ms | "
            "RadFilter: " +
            std::to_string(ms_filter) +
            "ms | "
            "OutConv: " +
            std::to_string(ms_out) +
            "ms || "
            "Total: " +
            std::to_string(ms_total) + "ms");

        return noiseRemovedPointCloud;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser