/**
 * @file OriengationMsg.hpp
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
  double roll;  //!< Roll value in radians
  double pitch; //!< Pitch value in radians
  double yaw;   //!< Yaw value in Radians
  OrientationMsg() {};
};
}