#pragma once
#include <string>
namespace fast::rf::messages::Pose {
struct PointMsg {
  double x;
  double y;
  double z;
  PointMsg(double x, double y, double z) : x(x), y(y), z(z) {}
  PointMsg() {}
};
struct PoseMsg {
  PointMsg point;

  PoseMsg() {}
};
} // namespace fast::rf::messages::Pose
