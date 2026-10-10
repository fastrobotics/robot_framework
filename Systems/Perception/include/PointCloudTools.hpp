/**
 * @file PointCloudTools.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-09
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <PointCloudMsg.hpp>
#include <cstdint>
#include <vector>
namespace fast::rf::PerceptionSystem {
    template <typename PointT>
    bool convertToPCL(const fast::rf::messages::SensorMsgs::PointCloudMsg& msg,
                      typename pcl::PointCloud<PointT>::Ptr& out_cloud);

    /**
     * @brief High-speed optimized conversion from PCL PointCloud back to PointCloudMsg.
     */
    template <typename PointT>
    bool convertFromPCL(const typename pcl::PointCloud<PointT>::Ptr& in_cloud,
                        fast::rf::messages::SensorMsgs::PointCloudMsg& out_msg);

}  // namespace fast::rf::PerceptionSystem