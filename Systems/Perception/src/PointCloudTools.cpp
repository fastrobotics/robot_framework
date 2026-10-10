#pragma GCC optimize("O3,inline,fast-math")

#include <PointCloudTools.hpp>
#include <PointFieldMsg.hpp>
namespace fast::rf::PerceptionSystem {
    void populateDefaultRgbdFields(fast::rf::messages::SensorMsgs::PointCloudMsg& out_msg) {
        using DataType = fast::rf::messages::SensorMsgs::PointFieldMsg::PointFieldDataType;
        out_msg.fields.clear();

        fast::rf::messages::SensorMsgs::PointFieldMsg f_x;
        f_x.name = "x";
        f_x.offset = 0;
        f_x.datatype = DataType::FLOAT32;
        f_x.count = 1;
        out_msg.fields.push_back(f_x);

        fast::rf::messages::SensorMsgs::PointFieldMsg f_y;
        f_y.name = "y";
        f_y.offset = 4;
        f_y.datatype = DataType::FLOAT32;
        f_y.count = 1;
        out_msg.fields.push_back(f_y);

        fast::rf::messages::SensorMsgs::PointFieldMsg f_z;
        f_z.name = "z";
        f_z.offset = 8;
        f_z.datatype = DataType::FLOAT32;
        f_z.count = 1;
        out_msg.fields.push_back(f_z);

        fast::rf::messages::SensorMsgs::PointFieldMsg f_rgb;
        f_rgb.name = "rgb";
        f_rgb.offset = 12;
        f_rgb.datatype = DataType::UINT32;
        f_rgb.count = 1;
        out_msg.fields.push_back(f_rgb);
    }

    // =========================================================================
    // OPTIMIZED IMPLEMENTATION: MSG -> PCL (PointXYZRGB)
    // =========================================================================
    template <>
    bool convertToPCL<pcl::PointXYZRGB>(const fast::rf::messages::SensorMsgs::PointCloudMsg& msg,
                                        pcl::PointCloud<pcl::PointXYZRGB>::Ptr& out_cloud) {
        out_cloud.reset(new pcl::PointCloud<pcl::PointXYZRGB>());
        out_cloud->width = msg.width;
        out_cloud->height = msg.height;
        out_cloud->is_dense = false;

        const size_t total_points = msg.width * msg.height;
        if (total_points == 0 || msg.data.empty())
            return false;

        const uint8_t* src_ptr = msg.data.data();
        const uint32_t point_step = msg.point_step;

        // Use reserve() instead of resize() so no elements are instantiated yet
        out_cloud->points.reserve(total_points);

        if (point_step == sizeof(pcl::PointXYZRGB)) {
            // Direct cast parsing assignment via safe iterator positioning
            const pcl::PointXYZRGB* raw_points = reinterpret_cast<const pcl::PointXYZRGB*>(src_ptr);
            out_cloud->points.assign(raw_points, raw_points + total_points);
        } else {
            // Fallback layout mapping path if strided offsets don't match 32-byte alignment footprints
            out_cloud->points.resize(total_points);
            void* dst_ptr = static_cast<void*>(out_cloud->points.data());
            uint8_t* dst_byte_ptr = static_cast<uint8_t*>(dst_ptr);

            for (size_t i = 0; i < total_points; ++i) {
                std::memcpy(dst_byte_ptr + (i * sizeof(pcl::PointXYZRGB)), src_ptr + (i * point_step), 16);
            }
        }

        out_cloud->header.stamp = static_cast<uint64_t>(msg.time_stamp * 1e6);
        return true;
    }

    // =========================================================================
    // OPTIMIZED IMPLEMENTATION: PCL -> MSG (PointXYZRGB)
    // =========================================================================
    template <>
    bool convertFromPCL<pcl::PointXYZRGB>(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& in_cloud,
                                          fast::rf::messages::SensorMsgs::PointCloudMsg& out_msg) {
        out_msg.height = in_cloud->height;
        out_msg.width = in_cloud->width;
        out_msg.time_stamp = static_cast<double>(in_cloud->header.stamp) / 1e6;
        out_msg.is_bigendian = false;
        out_msg.point_step = sizeof(pcl::PointXYZRGB);
        out_msg.row_step = out_msg.point_step * out_msg.width;

        populateDefaultRgbdFields(out_msg);

        const size_t total_bytes = out_msg.row_step * out_msg.height;
        out_msg.data.resize(total_bytes);

        if (total_bytes == 0 || in_cloud->points.empty())
            return false;

        // Fixed: Cast source pointer to const void* here as well
        const void* src_ptr = static_cast<const void*>(in_cloud->points.data());
        std::memcpy(out_msg.data.data(), src_ptr, total_bytes);
        return true;
    }

    template bool convertToPCL<pcl::PointXYZRGB>(const fast::rf::messages::SensorMsgs::PointCloudMsg&,
                                                 pcl::PointCloud<pcl::PointXYZRGB>::Ptr&);
    template bool convertFromPCL<pcl::PointXYZRGB>(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr&,
                                                   fast::rf::messages::SensorMsgs::PointCloudMsg&);

}  // namespace fast::rf::PerceptionSystem