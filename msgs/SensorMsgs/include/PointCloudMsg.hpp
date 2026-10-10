/**
 * @file PointCloudMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-01
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <cstddef>
#include <cstdint>
#include <string>

namespace fast::rf::messages::SensorMsgs {
    /**
     * @brief PointCloudMsg Definition of a Point Cloud
     *
     */
    struct PointCloudMsg {
        double time_stamp;  //!< Timestamp of data
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud;  //!< RGB point data and PCL metadata

        PointCloudMsg() : time_stamp(-1.0), point_cloud(new pcl::PointCloud<pcl::PointXYZRGB>) {}

        std::size_t size() const { return point_cloud ? point_cloud->size() : 0; }

        bool empty() const { return size() == 0; }

        std::string pretty() const {
            return "T: " + std::to_string(time_stamp) + " Point Count: " + std::to_string(size()) + "\n";
        }
        /**
         * @brief Helper function to create a gradient RGB Cloud
         *
         * @param dimension
         * @return PointCloudMsg
         */
        static PointCloudMsg generateRGBCloud(uint32_t dimension) {
            PointCloudMsg msg;
            msg.point_cloud->width = dimension;
            msg.point_cloud->height = dimension * dimension;
            msg.point_cloud->is_dense = true;
            msg.point_cloud->points.resize(static_cast<std::size_t>(dimension) * dimension * dimension);
            float maxDiv = (dimension > 1) ? static_cast<float>(dimension - 1) : 1.0f;

            for (uint32_t x = 0; x < dimension; ++x) {
                for (uint32_t y = 0; y < dimension; ++y) {
                    for (uint32_t z = 0; z < dimension; ++z) {
                        std::size_t pointIndex = ((static_cast<std::size_t>(x) * dimension) + y) * dimension + z;

                        auto& point = msg.point_cloud->points[pointIndex];
                        point.x = static_cast<float>(x) * 0.5f;
                        point.y = static_cast<float>(y) * 0.5f;
                        point.z = static_cast<float>(z) * 0.5f;

                        point.r = static_cast<uint8_t>((static_cast<float>(x) / maxDiv) * 255.0f);
                        point.g = static_cast<uint8_t>((static_cast<float>(y) / maxDiv) * 255.0f);
                        point.b = static_cast<uint8_t>((static_cast<float>(z) / maxDiv) * 255.0f);
                    }
                }
            }
            return msg;
        }
    };
}  // namespace fast::rf::messages::SensorMsgs
