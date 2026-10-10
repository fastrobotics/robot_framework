#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <vtkObject.h>

#include <PointCloudMsg.hpp>
#include <cstdint>
#include <cstdlib>
#include <iostream>

fast::rf::messages::SensorMsgs::PointCloudMsg createMockMessage(uint32_t num_points) {
    fast::rf::messages::SensorMsgs::PointCloudMsg msg;
    msg.time_stamp = 1712345678.9;
    msg.point_cloud->width = num_points;
    msg.point_cloud->height = 1;
    msg.point_cloud->is_dense = true;
    msg.point_cloud->points.resize(num_points);

    for (auto& point : msg.point_cloud->points) {
        point.x = 5.0f * std::rand() / (RAND_MAX + 1.0f);
        point.y = 5.0f * std::rand() / (RAND_MAX + 1.0f);
        point.z = 5.0f * std::rand() / (RAND_MAX + 1.0f);
        point.r = static_cast<uint8_t>(std::rand() % 256);
        point.g = static_cast<uint8_t>(std::rand() % 256);
        point.b = static_cast<uint8_t>(std::rand() % 256);
    }

    return msg;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    vtkObject::GlobalWarningDisplayOff();

    auto mock_msg = createMockMessage(5000);
    std::cout << "Generated PCL RGB-D cloud containing " << mock_msg.point_cloud->size() << " points.\n";

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud = mock_msg.point_cloud;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::VoxelGrid<pcl::PointXYZRGB> sor;
    sor.setInputCloud(cloud);
    sor.setLeafSize(0.3f, 0.3f, 0.3f);
    sor.filter(*cloud_filtered);
    std::cout << "Filtered point cloud count downsized to: " << cloud_filtered->size() << "\n";

    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Live RGB-D Viewer"));
    viewer->setBackgroundColor(0.05, 0.05, 0.1);
    viewer->setUseVbos(true);

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
