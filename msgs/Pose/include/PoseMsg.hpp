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
/**
 * @brief Pose Message Namespace
 *
 */
namespace fast::rf::messages::Pose {
/**
 * @brief
 *
 */
struct OrientationMsg {
  /**
   * @brief Roll Angle in radians
   *
   */
  double roll;
  /**
   * @brief Pitch Angle in radians
   *
   */
  double pitch;
  /**
   * @brief Yaw Angle in radians
   *
   */
  double yaw;
};
/**
 * @brief
 *
 */
struct OrientationWithCovarianceMsg {
  OrientationMsg orientation;
  std::vector<double> covariance;
  OrientationWithCovarianceMsg() { covariance.resize(36); }
};
/**
 * @brief
 *
 */
struct PointMsg {
  double x;
  double y;
  double z;
  PointMsg(double x, double y, double z) : x(x), y(y), z(z) {}
  PointMsg() {}
};
/**
 * @brief
 *
 */
struct PointWithCovarianceMsg {
  PointMsg point;
  std::vector<double> covariance;
  PointWithCovarianceMsg() { covariance.resize(36); }
};
/**
 * @brief
 *
 */
struct PoseMsg {
  double time_stamp{0.0};
  PointWithCovarianceMsg point;
  OrientationWithCovarianceMsg orientation;

  PoseMsg() {}
};
} // namespace fast::rf::messages::Pose
