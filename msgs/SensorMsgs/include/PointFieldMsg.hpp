/**
 * @file PointFieldMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-01
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <cstdint>
#include <string>
namespace fast::rf::messages::SensorMsgs {
    /**
     * @brief PointFieldMsg Definition
     *
     */
    struct PointFieldMsg {
        /**
         * @brief PointFieldDataType Enum definition for encoding
         *
         */
        enum class PointFieldDataType {
            UNKNOWN = 0,
            INT8 = 1,
            UINT8 = 2,
            INT16 = 3,
            UINT16 = 4,
            INT32 = 5,
            UINT32 = 6,
            FLOAT32 = 7,
            FLOAT64 = 8,
            END_OF_LIST = 9
        };
        std::string name;             //!< Name of field.  Common names: x,y,z,intensity,rgb,rgba
        uint32_t offset;              //!< Offset from start of point struct
        PointFieldDataType datatype;  //!< Datatype enumeration
        uint32_t count;               //!< How many elements in field
        PointFieldMsg() : name(""), offset(0), datatype(PointFieldDataType::UNKNOWN), count(0) {}
        /**
         * @brief Human readable version
         *
         * @param type
         * @return std::string
         */
        static std::string pretty(PointFieldDataType type) {
            switch (type) {
                case PointFieldDataType::UNKNOWN:
                    return "UNKNOWN";
                case PointFieldDataType::INT8:
                    return "INT8";
                case PointFieldDataType::UINT8:
                    return "UINT8";
                case PointFieldDataType::INT16:
                    return "INT16";
                case PointFieldDataType::UINT16:
                    return "UINT16";
                case PointFieldDataType::INT32:
                    return "INT32";
                case PointFieldDataType::UINT32:
                    return "UINT32";
                case PointFieldDataType::FLOAT32:
                    return "FLOAT32";
                case PointFieldDataType::FLOAT64:
                    return "FLOAT64";
                default:
                    return pretty(PointFieldDataType::UNKNOWN);
            }
        }
        /**
         * @brief Human readable version
         *
         * @return std::string
         */
        std::string pretty() {
            std::string str = "Field: " + name + " offset: " + std::to_string(offset) + " type: " + pretty(datatype) +
                              " count: " + std::to_string(count);
            return str;
        }
    };
}  // namespace fast::rf::messages::SensorMsgs
