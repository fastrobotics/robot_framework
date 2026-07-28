/**
 * @file OrientationMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-24
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <string>
#include <vector>
namespace fast::rf::messages::GeometryMsgs {

    /**
     * @brief Data Structure for encoding Orientation
     *
     */
    struct OrientationMsg {
        double roll;   //!< Roll value in radians
        double pitch;  //!< Pitch value in radians
        double yaw;    //!< Yaw value in Radians
        OrientationMsg(){};

        /**
         * @brief Human readable version of data
         *
         * @return std::string
         */
        std::string pretty() {
            std::string str = "R: " + std::to_string(roll) + " (rad) P: " + std::to_string(pitch) +
                              " (rad) Y: " + std::to_string(yaw) + " (rad)";
            return str;
        }
    };
}  // namespace fast::rf::messages::GeometryMsgs