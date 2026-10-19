# Point Cloud Object Extraction Pipeline (C++17 & PCL)

This guide provides a comprehensive walk-through for isolating individual objects and creating a structured **Object List** from an already downsampled 3D point cloud using **surface normals** and **FPFH (Fast Point Feature Histograms)** local descriptors.

Since objects are not guaranteed to rest on a flat surface, this pipeline uses a geometric **Region Growing Segmentation** approach. This technique splits objects at sharp surface transitions, gaps, and edges rather than relying on structural ground planes.

---

## 1. Object List Data Structure

We define a clean, modern C++17 structure (`DiscoveredObject`) to encapsulate all critical metadata for each identified object instance, including its spatial coordinates, oriented boundaries, and an aggregated global FPFH fingerprint.

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <Eigen/Dense>

// Type aliases for easier readability
using PointT  = pcl::PointXYZRGB; // Change to pcl::PointXYZ if color is not present
using NormalT = pcl::Normal;
using FpfhT   = pcl::FPFHSignature33;

struct DiscoveredObject {
    int id;
    size_t point_count;
    Eigen::Vector4f centroid;
    Eigen::Vector3f dimensions;     // Width, Height, Depth (Oriented Bounding Box)
    Eigen::Matrix3f rotation_matrix; // Orientation matrix of the object
    Eigen::VectorXf global_fpfh;     // Pooled 33-dimensional descriptor fingerprint
    pcl::PointCloud<PointT>::Ptr cloud_cluster;
};
```

---

## 2. Core Extraction Function

The `extractObjectList` function takes your downsampled input cloud, its surface normals, and its FPFH features. It groups contiguous regions using smooth surface continuity rules, calculates an **Oriented Bounding Box (OBB)** via inertia tensors, and pools point-level local histograms into a singular feature signature.

```cpp
#include <pcl/segmentation/region_growing.h>
#include <pcl/common/common.h>
#include <pcl/common/centroid.h>
#include <pcl/features/moment_of_inertia_estimation.h>

std::vector<DiscoveredObject> extractObjectList(
    const pcl::PointCloud<PointT>::Ptr& cloud,
    const pcl::PointCloud<NormalT>::Ptr& normals,
    const pcl::PointCloud<FpfhT>::Ptr& fpfh_features,
    float cluster_tolerance_deg = 3.0f, 
    int min_cluster_size = 50) 
{
    std::vector<DiscoveredObject> object_list;

    // 1. Configure and run Region Growing Segmentation
    pcl::RegionGrowing<PointT, NormalT> reg;
    reg.setMinClusterSize(min_cluster_size);
    reg.setMaxClusterSize(1000000);
    reg.setInputCloud(cloud);
    reg.setInputNormals(normals);
    
    // Configure normal proximity thresholds
    reg.setNumberOfNeighbours(30); 
    reg.setSmoothnessThreshold(cluster_tolerance_deg * M_PI / 180.0); // Degrees to Radians
    reg.setCurvatureThreshold(1.0); // Allows handling of moderately irregular surfaces

    std::vector<pcl::PointIndices> clusters;
    reg.extract(clusters);

    std::cout << "[Info] Region growing segmented " << clusters.size() << " discrete objects.\n";

    // 2. Process each isolated cluster independently
    int object_counter = 0;
    for (const auto& indices : clusters) {
        
        // Extract cluster subset
        pcl::PointCloud<PointT>::Ptr cluster_cloud(new pcl::PointCloud<PointT>);
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
        pcl::MomentOfInertiaEstimation<PointT> feature_extractor;
        feature_extractor.setInputCloud(cluster_cloud);
        feature_extractor.compute();

        PointT min_point_OBB, max_point_OBB;
        Eigen::Vector3f position;
        Eigen::Matrix3f rotational_matrix;

        feature_extractor.getOBB(min_point_OBB, max_point_OBB, position, rotational_matrix);
        Eigen::Vector3f dimensions(
            max_point_OBB.x - min_point_OBB.x,
            max_point_OBB.y - min_point_OBB.y,
            max_point_OBB.z - min_point_OBB.z
        );

        // 3. Pool local features into a Global Object Descriptor
        // Averaging the histogram bins across all component points inside this instance
        Eigen::VectorXf global_descriptor = Eigen::VectorXf::Zero(33);
        for (const auto& index : indices.indices) {
            const FpfhT& point_fpfh = (*fpfh_features)[index];
            for (int f = 0; f < 33; ++f) {
                global_descriptor[f] += point_fpfh.histogram[f];
            }
        }
        global_descriptor /= static_cast<float>(indices.indices.size());

        // 4. Populate object structure entry
        DiscoveredObject obj;
        obj.id = object_counter++;
        obj.point_count = indices.indices.size();
        obj.centroid = centroid;
        obj.dimensions = dimensions;
        obj.rotation_matrix = rotational_matrix;
        obj.global_fpfh = global_descriptor;
        obj.cloud_cluster = cluster_cloud;

        object_list.push_back(obj);
    }

    return object_list;
}
```

---

## 3. Executive Walk-Through Example (`main.cpp`)

Here is an example setup demonstrating how to orchestrate the pipeline within your program's execution routine.

```cpp
#include <pcl/io/pcd_io.h>

int main(int argc, char** argv) {
    // Instantiate target point clouds and feature maps
    pcl::PointCloud<PointT>::Ptr input_cloud(new pcl::PointCloud<PointT>);
    pcl::PointCloud<NormalT>::Ptr cloud_normals(new pcl::PointCloud<NormalT>);
    pcl::PointCloud<FpfhT>::Ptr cloud_fpfh(new pcl::PointCloud<FpfhT>);

    // [Populate data structures from source stream or files here]
    // Example: pcl::io::loadPCDFile("downsampled_cloud.pcd", *input_cloud);

    if (input_cloud->empty()) {
        std::cerr << "Input cloud is empty. Aborting execution.\n";
        return -1;
    }

    // Process pipeline
    std::vector<DiscoveredObject> my_objects = extractObjectList(input_cloud, cloud_normals, cloud_fpfh);

    // Output extracted manifest data to stdout
    std::cout << "\n=================================" << std::endl;
    std::cout << "    EXTRACTED OBJECT MANIFEST     " << std::endl;
    std::cout << "=================================\n" << std::endl;
    
    for (const auto& obj : my_objects) {
        std::cout << "Object ID:     " << obj.id << "\n"
                  << "  Points:      " << obj.point_count << "\n"
                  << "  Centroid:    [" << obj.centroid[0] << ", " << obj.centroid[1] << ", " << obj.centroid[2] << "]\n"
                  << "  Size(W,H,D): [" << obj.dimensions[0] << ", " << obj.dimensions[1] << ", " << obj.dimensions[2] << "]\n"
                  << "  FPFH Signature (First 3 bins): [" << obj.global_fpfh[0] << ", " << obj.global_fpfh[1] << ", " << obj.global_fpfh[2] << "]\n"
                  << "---------------------------------" << std::endl;
    }

    return 0;
}
```

---

## 4. Build Configuration (`CMakeLists.txt`)

Use this `CMakeLists.txt` configuration to pull the modern C++17 properties and coordinate dependencies for the required `PCL` modules.

```cmake
cmake_minimum_required(VERSION 3.10)
project(object_segmentation_pipeline)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Discover Point Cloud Library modules
find_package(PCL 1.10 REQUIRED COMPONENTS common features segmentation io)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(extract_objects main.cpp)
target_link_libraries(extract_objects ${PCL_LIBRARIES})
```

---

## 5. Downstream Applications of the Object List

* **Geometric Matching:** The calculated 33-dimensional `global_fpfh` vector can be passed straight into FLANN (Fast Library for Approximate Nearest Neighbors) or a simple k-NN index to compare against a catalog of pre-computed CAD models.
* **Orientation and Grasping:** The `centroid`, `dimensions`, and `rotation_matrix` describe a complete 6-DoF oriented bounding box for robotic arms or manipulation planners without wasting computational cycles on background terrain.
* **Classification Pipeline:** If building an object identification loop, the fixed-length `global_fpfh` profile serves as a feature vector input for machine learning classifiers like Support Vector Machines (SVM) or Random Forests.