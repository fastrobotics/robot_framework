/**
 * @file PointMsg.hpp
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
 * @brief Data Structure for encoding Points
 *
 */
struct PointMsg {
  double x; //!< X value in meters
  double y; //!< Y value in meters
  double z; //!< Z value in meters
  PointMsg() {};
};
}