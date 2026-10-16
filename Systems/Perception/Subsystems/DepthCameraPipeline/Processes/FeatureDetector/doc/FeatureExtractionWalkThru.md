# PCL RGB-D Feature Extraction Module (C++17)

This module provides a standalone, production-ready C++17 class wrapper for the **Point Cloud Library (PCL)**. It takes a preprocessed (noise-reduced and downsampled) colorized 3D point cloud from an RGB-D camera and extracts critical geometric features—specifically **Surface Normals** and **Fast Point Feature Histograms (FPFH)**—to prepare the data for downstream object clustering, registration, and recognition pipelines.

---

## 🚀 Key Features

*   **Modern C++17 Architecture:** Leverages standard smart pointers (`std::shared_ptr`), type aliases (`using`), and performance decorators (`noexcept`, `[[nodiscard]]`).
*   **RGB-D Compatibility:** Formatted exclusively around `pcl::PointXYZRGB` to natively preserve and utilize colorized sensor streams.
*   **Surface Normal Estimation:** Computes local surface geometry by fitting planes to localized point neighborhoods.
*   **FPFH Descriptor Generation:** Extracts a 33-dimensional structural fingerprint for every point, ideal for object matching and pipeline registration.
*   **Thread-Safe Const Inputs:** Keeps raw input data protected by enforcing strict `const` pointer inputs.

---

## 📦 Directory Structure

```text
.
├── FeatureExtractor.h     # Class declaration & configurations
├── FeatureExtractor.cpp   # Implementation details using PCL algorithms
└── main.cpp               # Sample integration / pipeline entry point
```

---

## 💻 Codebase

### 1. Header File (`FeatureExtractor.h`)
```cpp
#pragma once

#include <memory>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/fpfh.h>
#include <pcl/search/kdtree.h>

/**
 * @class FeatureExtractor
 * @brief Manages the extraction of local geometric features from preprocessed RGB-D point clouds.
 */
class FeatureExtractor {
public:
    // C++17 Type Aliases modified to support RGB-D point type
    using PointCloudXYZRGB = pcl::PointCloud<pcl::PointXYZRGB>;
    using PointCloudNormal = pcl::PointCloud<pcl::Normal>;
    using PointCloudFPFH = pcl::PointCloud<pcl::FPFHSignature33>;

    FeatureExtractor() = default;
    ~FeatureExtractor() = default;

    // Setters
    void setInputCloud(const PointCloudXYZRGB::ConstPtr& cloud);
    void setNormalSearchRadius(double radius) noexcept { m_normalRadius = radius; }
    void setFpfhSearchRadius(double radius) noexcept { m_fpfhRadius = radius; }
    void setSensorViewpoint(float x, float y, float z) noexcept { m_viewpoint = {x, y, z}; }

    // Core execution pipeline
    bool computeFeatures();

    // Getters
    [[nodiscard]] PointCloudNormal::Ptr getNormals() const noexcept { return m_normals; }
    [[nodiscard]] PointCloudFPFH::Ptr getFpfhFeatures() const noexcept { return m_fpfhFeatures; }

private:
    // Input Cloud Data using colorized point type
    PointCloudXYZRGB::ConstPtr m_inputCloud{ nullptr };

    // Tuning Parameters (Defaults scale with a ~1cm voxel leaf size)
    double m_normalRadius{ 0.03 }; // 3 cm
    double m_fpfhRadius{ 0.05 };   // 5 cm
    struct { float x{0.0f}, y{0.0f}, z{0.0f}; } m_viewpoint; // Camera coordinate frame origin

    // Internal Output Allocations
    PointCloudNormal::Ptr m_normals{ std::make_shared<PointCloudNormal>() };
    PointCloudFPFH::Ptr m_fpfhFeatures{ std::make_shared<PointCloudFPFH>() };
};
```

### 2. Implementation File (`FeatureExtractor.cpp`)
```cpp
#include "FeatureExtractor.h"
#include <iostream>

void FeatureExtractor::setInputCloud(const PointCloudXYZRGB::ConstPtr& cloud) {
    m_inputCloud = cloud;
}

bool FeatureExtractor::computeFeatures() {
    if (!m_inputCloud || m_inputCloud->empty()) {
        std::cerr << "[FeatureExtractor] Error: Input RGB-D cloud is empty or null.\n";
        return false;
    }

    // 1. Shared spatial optimization index via a KD-Tree matching the PointXYZRGB type
    auto tree = std::make_shared<pcl::search::KdTree<pcl::PointXYZRGB>>();

    // 2. Extract Surface Normals
    std::cout << "[FeatureExtractor] Computing surface normals from RGB-D data...\n";
    // First template is input type (XYZRGB), second is output type (Normal)
    pcl::NormalEstimation<pcl::PointXYZRGB, pcl::Normal> ne;
    ne.setInputCloud(m_inputCloud);
    ne.setSearchMethod(tree);
    ne.setRadiusSearch(m_normalRadius);
    ne.setViewPoint(m_viewpoint.x, m_viewpoint.y, m_viewpoint.z);
    
    m_normals->clear();
    ne.compute(*m_normals);

    if (m_normals->empty()) {
        std::cerr << "[FeatureExtractor] Error: Failed to estimate normals.\n";
        return false;
    }

    // 3. Extract FPFH Features
    std::cout << "[FeatureExtractor] Computing FPFH features...\n";
    // First template must match the input type (XYZRGB)
    pcl::FPFHEstimation<pcl::PointXYZRGB, pcl::Normal, pcl::FPFHSignature33> fpfh;
    fpfh.setInputCloud(m_inputCloud);
    fpfh.setInputNormals(m_normals);
    fpfh.setSearchMethod(tree);
    fpfh.setRadiusSearch(m_fpfhRadius);

    m_fpfhFeatures->clear();
    fpfh.compute(*m_fpfhFeatures);

    std::cout << "[FeatureExtractor] Successfully extracted " 
              << m_fpfhFeatures->size() << " feature descriptors.\n";
              
    return !m_fpfhFeatures->empty();
}
```

### 3. Usage Example (`main.cpp`)
```cpp
#include "FeatureExtractor.h"
#include <pcl/io/pcd_io.h>
#include <iostream>

int main() {
    // Instantiate your cloud pointer using RGB point type
    auto cleanCloud = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();
    
    // Load your noise-reduced, downsampled RGB-D data
    if (pcl::io::loadPCDFile<pcl::PointXYZRGB>("preprocessed_rgbd_cloud.pcd", *cleanCloud) == -1) {
        std::cerr << "Couldn't read file preprocessed_rgbd_cloud.pcd \n";
        return -1;
    }

    // Initialize extractor
    FeatureExtractor extractor;
    extractor.setInputCloud(cleanCloud);
    
    // Tuning parameters manually
    extractor.setNormalSearchRadius(0.03); // 3cm sphere search for surface orientation
    extractor.setFpfhSearchRadius(0.06);   // 6cm sphere search for descriptive context

    // Execute pipeline
    if (extractor.computeFeatures()) {
        auto normals = extractor.getNormals();
        auto fpfhDescriptors = extractor.getFpfhFeatures();
        
        std::cout << "Data extraction complete. Extracted data points match: " 
                  << (normals->size() == fpfhDescriptors->size() ? "Yes" : "No") << "\n";
        std::cout << "Ready for object clustering pipeline.\n";
    }

    return 0;
}
```

---

## 🛠️ Tuning Guide

To get clean outputs without crashing your software with `NaN` (Not a Number) errors, balance your radii using this rule of thumb:

| Parameter                | Recommended Relationship          | Purpose                                                                             |
| :----------------------- | :-------------------------------- | :---------------------------------------------------------------------------------- |
| **Normal Search Radius** | **2x to 3x** your Voxel Leaf Size | Fits local tangent planes without swallowing micro-features.                        |
| **FPFH Search Radius**   | **2x** your Normal Search Radius  | Looks at wider neighborhoods to compute angular histograms across different planes. |

*Example:* If your downsampling step used a voxel size of `0.01` (1cm), set your Normal Radius to `0.03` (3cm) and your FPFH Radius to `0.06` (6cm).
