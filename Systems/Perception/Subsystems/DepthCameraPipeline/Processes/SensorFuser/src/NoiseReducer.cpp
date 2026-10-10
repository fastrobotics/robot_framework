#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/search/kdtree.h>

#include <Infrastructure/Logger.hpp>
#include <NoiseReducer.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    bool NoiseReducer::init() { return true; }
    fast::rf::messages::SensorMsgs::PointCloudMsg NoiseReducer::reduceNoise(
        const fast::rf::messages::SensorMsgs::PointCloudMsg& overlapRemovedPointCloud) {
        fast::rf::messages::SensorMsgs::PointCloudMsg noiseRemovedPointCloud;
        bool noiseFilterEnable = true;

        pcl::PointCloud<pcl::PointXYZRGB>::Ptr pclCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
        convertToPCL<pcl::PointXYZRGB>(overlapRemovedPointCloud, pclCloud);
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr pclCloudFiltered(new pcl::PointCloud<pcl::PointXYZRGB>);
        if (noiseFilterEnable == true) {
            if (pclCloud->empty()) {
                return overlapRemovedPointCloud;
            }

            // =================================================================
            // STEP 1: Fast NaN Removal (Essential)
            // =================================================================
            pcl::PointCloud<pcl::PointXYZRGB>::Ptr cleanCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
            std::vector<int> nan_indices;
            pcl::removeNaNFromPointCloud(*pclCloud, *cleanCloud, nan_indices);

            if (cleanCloud->empty())
                return overlapRemovedPointCloud;

            // =================================================================
            // STEP 2: Downsample First (Voxel Grid)
            // This cuts down a 600k cloud to ~20k-40k points in milliseconds,
            // making the subsequent Radius Filter exponentially faster.
            // =================================================================
            pcl::PointCloud<pcl::PointXYZRGB>::Ptr downsampledCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
            pcl::VoxelGrid<pcl::PointXYZRGB> vg;
            vg.setInputCloud(cleanCloud);
            // Leaf size = voxel size in meters.
            // 0.02f = 2cm cubes. Increase to 0.03f or 0.04f if your laptop still struggles.
            double voxelSize = 0.5f;
            vg.setLeafSize(voxelSize, voxelSize, voxelSize);
            vg.filter(*downsampledCloud);

            if (downsampledCloud->empty())
                return overlapRemovedPointCloud;

            // =================================================================
            // STEP 3: Optimized Radius Outlier Removal
            // =================================================================
            try {
                pcl::RadiusOutlierRemoval<pcl::PointXYZRGB> ror;
                ror.setInputCloud(downsampledCloud);

                // 1. Create a fast, explicitly defined spatial lookup tree
                pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZRGB>);

                // 2. Tell the filter to use this specific search method
                ror.setSearchMethod(tree);

                // 3. Keep the search window small so the tree resolves queries fast
                ror.setRadiusSearch(0.04);       // 4cm radius
                ror.setMinNeighborsInRadius(4);  // Lowered to match the smaller radius

                ror.filter(*pclCloudFiltered);

                std::size_t filteredOutCount = pclCloud->size() - pclCloudFiltered->size();
                double percentRemoved = 100.0 * (double)filteredOutCount / ((double)pclCloud->size());
                fast::rf::Logger::logWarn("Filtered Out: " + std::to_string(filteredOutCount) +
                                          " Perc: " + std::to_string(percentRemoved));
            } catch (const std::exception& e) {
                fast::rf::Logger::logError("PCL Filter threw an exception: " + std::string(e.what()));
                pclCloudFiltered = pclCloud;
            }
        } else {
            pclCloudFiltered = pclCloud;
        }

        convertFromPCL<pcl::PointXYZRGB>(pclCloudFiltered, noiseRemovedPointCloud);

        return noiseRemovedPointCloud;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser