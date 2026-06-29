/**
 * @file Vector3DMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-24
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once
#include <cstdint>
#include <vector>
namespace fast::rf::messages::StandardMsgs {

/**
 * @brief 3D Vector
 *
 */
struct Vector3DMsg {
    double x;  //!< X Axis
    double y;  //!< Y Axis
    double z;  //!< Z Axis
    Vector3DMsg() : x(0.0), y(0.0), z(0.0) {}
};
}  // namespace fast::rf::messages::StandardMsgs