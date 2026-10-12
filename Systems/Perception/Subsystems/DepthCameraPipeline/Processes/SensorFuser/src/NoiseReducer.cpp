#include <pcl/common/io.h>
#include <pcl/filters/filter.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/search/kdtree.h>

#include <Infrastructure/Logger.hpp>
#include <NoiseReducer.hpp>
#include <cstddef>
#include <cstdint>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    namespace {
        void radiusOutlierRemovalParallel(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr& input,
                                          pcl::PointCloud<pcl::PointXYZRGB>& output, double radius, int min_neighbors) {
            pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZRGB>(false));
            tree->setInputCloud(input);

            const int required_neighbors = min_neighbors + 1;
            const double radius_squared = radius * radius;
            std::vector<uint8_t> is_inlier(input->size(), 0);
            const auto point_count = static_cast<std::ptrdiff_t>(input->size());

#pragma omp parallel
            {
                pcl::Indices neighbor_indices;
                std::vector<float> neighbor_distances;

#pragma omp for schedule(static)
                for (std::ptrdiff_t index = 0; index < point_count; ++index) {
                    const int neighbor_count = tree->nearestKSearch(static_cast<int>(index), required_neighbors,
                                                                    neighbor_indices, neighbor_distances);
                    if (neighbor_count == required_neighbors &&
                        neighbor_distances[neighbor_count - 1] <= radius_squared) {
                        is_inlier[static_cast<std::size_t>(index)] = 1;
                    }
                }
            }

            pcl::Indices inlier_indices;
            inlier_indices.reserve(input->size());
            for (std::size_t index = 0; index < is_inlier.size(); ++index) {
                if (is_inlier[index] != 0)
                    inlier_indices.push_back(static_cast<int>(index));
            }
            pcl::copyPointCloud(*input, inlier_indices, output);
        }
    }  // namespace

    bool NoiseReducer::init() { return true; }
    fast::rf::messages::SensorMsgs::PointCloudMsg NoiseReducer::reduceNoise(
        const fast::rf::messages::SensorMsgs::PointCloudMsg& overlapRemovedPointCloud) {
        fast::rf::messages::SensorMsgs::PointCloudMsg noiseRemovedPointCloud;
        noiseRemovedPointCloud.time_stamp = overlapRemovedPointCloud.time_stamp;
        bool noiseFilterEnable = false;

        if (!overlapRemovedPointCloud.point_cloud) {
            fast::rf::Logger::logError("PointCloudMsg contains a null PCL point cloud.");
            return noiseRemovedPointCloud;
        }
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr pclCloud = overlapRemovedPointCloud.point_cloud;

        pcl::PointCloud<pcl::PointXYZRGB>::Ptr pclCloudFiltered(new pcl::PointCloud<pcl::PointXYZRGB>);

        if (noiseFilterEnable == true) {
            if (pclCloud->empty()) {
                return overlapRemovedPointCloud;
            }

            // =================================================================
            // TIME STAGE 1: Fast NaN Removal
            // =================================================================
            pcl::PointCloud<pcl::PointXYZRGB>::Ptr cleanCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
            std::vector<int> nan_indices;
            pcl::removeNaNFromPointCloud(*pclCloud, *cleanCloud, nan_indices);
            cleanCloud->is_dense = true;

            if (cleanCloud->empty())
                return overlapRemovedPointCloud;

            // =================================================================
            // TIME STAGE 2: Voxel Grid Downsampling
            // =================================================================
            pcl::PointCloud<pcl::PointXYZRGB>::Ptr downsampledCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
            pcl::VoxelGrid<pcl::PointXYZRGB> vg;
            vg.setInputCloud(cleanCloud);
            vg.setLeafSize(m_voxelSize_m, m_voxelSize_m, m_voxelSize_m);
            vg.filter(*downsampledCloud);

            if (downsampledCloud->empty())
                return overlapRemovedPointCloud;

            // =================================================================
            // TIME STAGE 3: Radius Outlier Removal Filter
            // =================================================================
            try {
                radiusOutlierRemovalParallel(downsampledCloud, *pclCloudFiltered, m_radius_m, m_minNeighborCount);

                std::size_t filteredOutCount = pclCloud->size() - pclCloudFiltered->size();
                double percentRemoved = 100.0 * static_cast<double>(filteredOutCount) / pclCloud->size();
                fast::rf::Logger::logDebug("Start Size: " + std::to_string(pclCloud->size()) +
                                           " Filtered Out: " + std::to_string(filteredOutCount) +
                                           " Perc: " + std::to_string(percentRemoved));
            } catch (const std::exception& e) {
                fast::rf::Logger::logError("PCL Filter threw an exception: " + std::string(e.what()));
                pclCloudFiltered = pclCloud;
            }
        } else {
            pclCloudFiltered = pclCloud;
        }

        noiseRemovedPointCloud.point_cloud = pclCloudFiltered;
        return noiseRemovedPointCloud;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser