#pragma once
#include <string>
#include <vector>
namespace fast::rf::messages::Pose {
struct OrientationMsg {
  double roll;
  double pitch;
  double yaw;
};
struct OrientationWithCovarianceMsg {
  OrientationMsg orientation;
  std::vector<double> covariance;
  OrientationWithCovarianceMsg() { covariance.resize(36); }
};
struct PointMsg {
  double x;
  double y;
  double z;
  PointMsg(double x, double y, double z) : x(x), y(y), z(z) {}
  PointMsg() {}
};
struct PointWithCovarianceMsg {
  PointMsg point;
  std::vector<double> covariance;
  PointWithCovarianceMsg() { covariance.resize(36); }
};
struct PoseMsg {
  double time_stamp{0.0};
  PointWithCovarianceMsg point;
  OrientationWithCovarianceMsg orientation;

  PoseMsg() {}
};
} // namespace fast::rf::messages::Pose
