/**
 * @file GeometryMsg.hpp
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

#include <StandardMsg.hpp>
using namespace fast::rf::messages::Standard;
/**
 * @brief Geometry Message Namespace
 *
 */
namespace fast::rf::messages::Geometry {
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

/**
 * @brief Data Structure for encoding Pose (Position and Orientation)
 *
 */
struct PoseMsg {
  PointMsg position;          //!< Position
  OrientationMsg orientation; //!< Euler Orientation
  PoseMsg() {};
};
/**
 * @brief Data Structure for encoding Velocity (linear and angular)
 *
 */
struct TwistMsg {
  Vector3DMsg linear;  //!< Linear Velocity
  Vector3DMsg angular; //!< Angular velocity
  TwistMsg() {};
};

/**
 * @brief Data Structure for encoding Pose and Covariance
 *
 */
struct PoseWithCovarianceMsg {
  static inline constexpr uint16_t COV_X =
      Covariance6DMsg::X1; //!< Covariance representing X Position.
  static inline constexpr uint16_t COV_Y =
      Covariance6DMsg::X2; //!< Covariance representing Y Position.
  static inline constexpr uint16_t COV_Z =
      Covariance6DMsg::X3; //!< Covariance representing Z Position.
  static inline constexpr uint16_t COV_ROLL =
      Covariance6DMsg::X4; //!< Covariance representing Roll Orientation.
  static inline constexpr uint16_t COV_PITCH =
      Covariance6DMsg::X5; //!< Covariance representing Pitch Orientationn.
  static inline constexpr uint16_t COV_YAW =
      Covariance6DMsg::X6;    //!< Covariance representing Yaw Orientation.
  PoseMsg pose;               //!< 6D Pose
  Covariance6DMsg covariance; //!< Error estimate of Pose
  PoseWithCovarianceMsg() {};
};

/**
 * @brief Data Structure for encoding Velocity and Covariance
 *
 */
struct TwistWithCovarianceMsg {
  static inline constexpr uint16_t COV_LINEAR_X =
      Covariance6DMsg::X1; //!< Covariance representing X Linear Velocity.
  static inline constexpr uint16_t COV_LINEAR_Y =
      Covariance6DMsg::X2; //!< Covariance representing Y Linear Velocity.
  static inline constexpr uint16_t COV_LINEAR_Z =
      Covariance6DMsg::X3; //!< Covariance representing Z Linear Velocity.
  static inline constexpr uint16_t COV_ANGULAR_ROLL =
      Covariance6DMsg::X4; //!< Covariance representing Roll Angular Velocity.
  static inline constexpr uint16_t COV_ANGULAR_PITCH =
      Covariance6DMsg::X5; //!< Covariance representing Pitch Angular Velocity.
  static inline constexpr uint16_t COV_ANGULAR_YAW =
      Covariance6DMsg::X6;    //!< Covariance representing Yaw Angular Velocity.
  TwistMsg twist;             //!< 6D Velocity
  Covariance6DMsg covariance; //!< Error estimate of velocity
  TwistWithCovarianceMsg() {};
};

/**
 * @brief Data structure for encoding Odometry
 *
 */
struct OdomMsg {
  double time_stamp;            //!< Timestamp of reported odometry
  PoseWithCovarianceMsg pose;   //!< Pose and Error Estimate
  TwistWithCovarianceMsg twist; //!< Velocity and Error Estimate
  OdomMsg() {};
};
} // namespace fast::rf::messages::Geometry
