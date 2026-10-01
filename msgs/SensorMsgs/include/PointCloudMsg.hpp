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
#include "PointFieldMsg.hpp"
namespace fast::rf::messages::SensorMsgs {
    /**
     * @brief PointCloudMsg Definition of a Point Cloud
     *
     */
    struct PointCloudMsg {
        double time_stamp;                  //!< Timestamp of data
        uint64_t seq;                       //!< Sequence number
        uint32_t height;                    //!< 2D Structure Height
        uint32_t width;                     //!< 2D Structure Width
        std::vector<PointFieldMsg> fields;  //!< Describe channels and layout in binary blob
        bool is_bigendian;                  //!< Big Endian Notation?
        uint32_t point_step;                //!< Length of a point in bytes
        uint32_t row_step;                  //!< Lenght of a row in bytes
        std::vector<uint8_t> data;          //!< Actual point data, size is (row_step *height)
        bool is_dense;                      //!< True if there are no invalid points
        PointCloudMsg() : time_stamp(-1.0), seq(0) {}
        std::string pretty() {
            std::string str = "T: " + std::to_string(time_stamp) + " seq: " + std::to_string(seq) +
                              " Point Count: " + std::to_string(data.size()) + "\n";
            str += "Fields (" + std::to_string(fields.size()) + ")\n";
            uint16_t index = 0;
            for (auto field : fields) {
                str += "\t[" + std::to_string(index) + "/" + std::to_string(fields.size()) + "] " + field.pretty();
            }
            return str;
        }
    };
}  // namespace fast::rf::messages::SensorMsgs
