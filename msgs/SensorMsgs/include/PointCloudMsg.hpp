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
#include <cstring>
#include <vector>

#include "PointFieldMsg.hpp"
namespace fast::rf::messages::SensorMsgs {
    /**
     * @brief PointCloudMsg Definition of a Point Cloud
     *
     */
    struct PointCloudMsg {
        double time_stamp;                  //!< Timestamp of data
        uint32_t height;                    //!< 2D Structure Height
        uint32_t width;                     //!< 2D Structure Width
        std::vector<PointFieldMsg> fields;  //!< Describe channels and layout in binary blob
        bool is_bigendian;                  //!< Big Endian Notation?
        uint32_t point_step;                //!< Length of a point in bytes
        uint32_t row_step;                  //!< Lenght of a row in bytes
        std::vector<uint8_t> data;          //!< Actual point data, size is (row_step *height)
        bool is_dense;                      //!< True if there are no invalid points
        PointCloudMsg() : time_stamp(-1.0), is_bigendian(false) {}
        std::string pretty() {
            std::string str =
                "T: " + std::to_string(time_stamp) + " Point Count: " + std::to_string(data.size()) + "\n";
            str += "Fields (" + std::to_string(fields.size()) + ")\n";
            uint16_t index = 0;
            for (auto field : fields) {
                str += "\t[" + std::to_string(index) + "/" + std::to_string(fields.size()) + "] " + field.pretty();
            }
            return str;
        }
        /**
         * @brief Helper function to create a gradient RGB Cloud
         *
         * @param dimension
         * @return PointCloudMsg
         */
        static PointCloudMsg generateRGBCloud(uint32_t dimension) {
            PointCloudMsg msg;
            msg.width = dimension;
            msg.height = dimension * dimension;
            msg.is_bigendian = false;
            msg.is_dense = true;
            SensorMsgs::PointFieldMsg fieldX;
            fieldX.name = "x";
            fieldX.offset = 0;
            fieldX.datatype = SensorMsgs::PointFieldMsg::PointFieldDataType::FLOAT32;
            fieldX.count = 1;
            SensorMsgs::PointFieldMsg fieldY;
            fieldY.name = "y";
            fieldY.offset = 4;
            fieldY.datatype = SensorMsgs::PointFieldMsg::PointFieldDataType::FLOAT32;
            fieldY.count = 1;
            SensorMsgs::PointFieldMsg fieldZ;
            fieldZ.name = "z";
            fieldZ.offset = 8;
            fieldZ.datatype = SensorMsgs::PointFieldMsg::PointFieldDataType::FLOAT32;
            fieldZ.count = 1;
            SensorMsgs::PointFieldMsg fieldRGB;
            fieldRGB.name = "rgb";
            fieldRGB.offset = 12;
            fieldRGB.datatype = SensorMsgs::PointFieldMsg::PointFieldDataType::UINT32;
            fieldRGB.count = 1;
            msg.fields = {fieldX, fieldY, fieldZ, fieldRGB};
            msg.point_step = 4 * 4;
            msg.row_step = msg.width * msg.point_step;
            msg.data.resize(msg.height * msg.row_step);
            float maxDiv = (dimension > 1) ? static_cast<float>(dimension - 1) : 1.0f;

            for (uint32_t x = 0; x < dimension; ++x) {
                for (uint32_t y = 0; y < dimension; ++y) {
                    for (uint32_t z = 0; z < dimension; ++z) {
                        size_t rowIndex = (x * dimension) + y;
                        size_t colIndex = z;
                        size_t byteOffset = (rowIndex * msg.row_step) + (colIndex * msg.point_step);

                        // Compute physical spatial coordinates (0.5 meter steps)
                        float x_pos = static_cast<float>(x) * 0.5f;
                        float y_pos = static_cast<float>(y) * 0.5f;
                        float z_pos = static_cast<float>(z) * 0.5f;

                        // Scale color gradients (0-255) safely mapped across the full range
                        uint8_t r = static_cast<uint8_t>((static_cast<float>(x) / maxDiv) * 255.0f);
                        uint8_t g = static_cast<uint8_t>((static_cast<float>(y) / maxDiv) * 255.0f);
                        uint8_t b = static_cast<uint8_t>((static_cast<float>(z) / maxDiv) * 255.0f);
                        uint8_t a = 0;

                        // Pack color fields into a standard B-G-R-A uint32_t layout
                        uint32_t rgb = 0;
                        rgb |= (static_cast<uint32_t>(b) << 0);
                        rgb |= (static_cast<uint32_t>(g) << 8);
                        rgb |= (static_cast<uint32_t>(r) << 16);
                        rgb |= (static_cast<uint32_t>(a) << 24);

                        // Write binary values straight into byte vector locations via standard memcpy
                        std::memcpy(&msg.data[byteOffset + 0], &x_pos, 4);
                        std::memcpy(&msg.data[byteOffset + 4], &y_pos, 4);
                        std::memcpy(&msg.data[byteOffset + 8], &z_pos, 4);
                        std::memcpy(&msg.data[byteOffset + 12], &rgb, 4);
                    }
                }
            }
            return msg;
        }
    };
}  // namespace fast::rf::messages::SensorMsgs
