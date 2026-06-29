/**
 * @file PoseMsg.hpp
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

#include <PointMsg.hpp>
#include <OrientationMsg.hpp>
namespace fast::rf::messages::GeometryMsgs {



/**
 * @brief Data Structure for encoding Pose (Position and Orientation)
 *
 */
struct PoseMsg {
  PointMsg position;          //!< Position
  OrientationMsg orientation; //!< Euler Orientation
  PoseMsg() {};
};
}