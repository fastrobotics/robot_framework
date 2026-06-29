

/**
 * @file PoseWithCovarianceMsg.hpp
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

#include <PoseMsg.hpp>
#include <Covariance6DMsg.hpp>
using namespace fast::rf::messages::StandardMsgs;

namespace fast::rf::messages::GeometryMsgs {


/**
 * @brief Data Structure for encoding Pose and Covariance
 *
 */
struct PoseWithCovarianceMsg {
  static inline constexpr uint16_t COV_X =
      Covariance6DMsg::X1; //!< Covariance Index representing X Position.
  static inline constexpr uint16_t COV_Y =
      Covariance6DMsg::X2; //!< Covariance Index representing Y Position.
  static inline constexpr uint16_t COV_Z =
      Covariance6DMsg::X3; //!< Covariance Index representing Z Position.
  static inline constexpr uint16_t COV_ROLL =
      Covariance6DMsg::X4; //!< Covariance Index representing Roll Orientation.
  static inline constexpr uint16_t COV_PITCH =
      Covariance6DMsg::X5; //!< Covariance Index representing Pitch
                           //!< Orientationn.
  static inline constexpr uint16_t COV_YAW =
      Covariance6DMsg::X6; //!< Covariance Index representing Yaw Orientation.
  PoseMsg pose;            //!< 6D Pose
  Covariance6DMsg covariance; //!< Error estimate of Pose. Diagonal
                              //!< elements representing the following: >0: Real
                              //!< values; =0: Unsupported; <0: Unknown
  PoseWithCovarianceMsg() {};
};
}