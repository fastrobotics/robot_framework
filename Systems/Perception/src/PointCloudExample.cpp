#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <vtkObject.h>

#include <PointCloudTools.hpp>
#include <iostream>
fast::rf::messages::SensorMsgs::PointCloudMsg createMockMessage(uint32_t num_points) {
    fast::rf::messages::SensorMsgs::PointCloudMsg msg;
    msg.time_stamp = 1712345678.9;
    msg.height = 1;
    msg.width = num_points;
    msg.is_bigendian = false;

    // Fix: Match PCL's true internal layout structure step size exactly
    msg.point_step = sizeof(pcl::PointXYZRGB);  // Equal to 32 bytes due to Eigen structural alignment rules
    msg.row_step = msg.point_step * msg.width;

    msg.fields.clear();
    using DataType = fast::rf::messages::SensorMsgs::PointFieldMsg::PointFieldDataType;

    fast::rf::messages::SensorMsgs::PointFieldMsg f_x;
    f_x.name = "x";
    f_x.offset = offsetof(pcl::PointXYZRGB, x);
    f_x.datatype = DataType::FLOAT32;
    f_x.count = 1;
    msg.fields.push_back(f_x);

    fast::rf::messages::SensorMsgs::PointFieldMsg f_y;
    f_y.name = "y";
    f_y.offset = offsetof(pcl::PointXYZRGB, y);
    f_y.datatype = DataType::FLOAT32;
    f_y.count = 1;
    msg.fields.push_back(f_y);

    fast::rf::messages::SensorMsgs::PointFieldMsg f_z;
    f_z.name = "z";
    f_z.offset = offsetof(pcl::PointXYZRGB, z);
    f_z.datatype = DataType::FLOAT32;
    f_z.count = 1;
    msg.fields.push_back(f_z);

    fast::rf::messages::SensorMsgs::PointFieldMsg f_rgb;
    f_rgb.name = "rgb";
    f_rgb.offset = offsetof(pcl::PointXYZRGB, rgb);
    f_rgb.datatype = DataType::UINT32;
    f_rgb.count = 1;
    msg.fields.push_back(f_rgb);

    // Resize container data layout footprint
    msg.data.resize(msg.row_step);

    // Fix: Cast directly to PCL points during generation to mimic matching layout structures
    pcl::PointXYZRGB* points_ptr = reinterpret_cast<pcl::PointXYZRGB*>(msg.data.data());

    for (uint32_t i = 0; i < num_points; ++i) {
        // Generate values tightly within a visible 5x5x5 coordinate viewport area
        points_ptr[i].x = 5.0f * rand() / (RAND_MAX + 1.0f);
        points_ptr[i].y = 5.0f * rand() / (RAND_MAX + 1.0f);
        points_ptr[i].z = 5.0f * rand() / (RAND_MAX + 1.0f);

        // Generate colors (0-255)
        uint8_t r = rand() % 256;
        uint8_t g = rand() % 256;
        uint8_t b = rand() % 256;

        // Pack colors tightly into the structure format using PCL bit shifting
        uint32_t rgb = ((uint32_t)r << 16 | (uint32_t)g << 8 | (uint32_t)b);
        points_ptr[i].rgb = *reinterpret_cast<float*>(&rgb);
    }

    return msg;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    vtkObject::GlobalWarningDisplayOff();

    // 1. Generate aligned RGB-D content container
    auto mock_msg = createMockMessage(5000);
    std::cout << "Generated agnostic RGB-D message containing " << mock_msg.width << " data points.\n";

    // 2. Map data
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
    fast::rf::PerceptionSystem::convertToPCL<pcl::PointXYZRGB>(mock_msg, cloud);
    std::cout << "Successfully parsed RGB-D binary blob into pcl::PointCloud format.\n";

    // 3. Downsample filter
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::VoxelGrid<pcl::PointXYZRGB> sor;
    sor.setInputCloud(cloud);
    sor.setLeafSize(0.3f, 0.3f, 0.3f);  // Smaller leaf size so points stay clear in a 5m cluster
    sor.filter(*cloud_filtered);
    std::cout << "Filtered point cloud count downsized to: " << cloud_filtered->size() << "\n";

    // 4. Render window
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Live RGB-D Viewer"));
    viewer->setBackgroundColor(0.05, 0.05, 0.1);
    viewer->setUseVbos(true);

    // Fix: explicitly pass the standard RGB handler to the visualizer to override default white fallback layers
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb_handler(cloud);
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb_filtered_handler(cloud_filtered);

    viewer->addPointCloud<pcl::PointXYZRGB>(cloud, rgb_handler, "original_cloud");
    viewer->addPointCloud<pcl::PointXYZRGB>(cloud_filtered, rgb_filtered_handler, "filtered_cloud");

    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "original_cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 8, "filtered_cloud");

    viewer->addCoordinateSystem(1.0);
    viewer->initCameraParameters();

    std::cout << "Starting native VTK visualization. Close the graphics viewport to finish.\n";
    viewer->spin();

    return 0;
}