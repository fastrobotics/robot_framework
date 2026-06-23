#pragma once
#include <string>
namespace fast::fr::messages {
struct PoseMsg {
  double x;
  double y;
  double z;
  PoseMsg(double x, double y, double z) : x(x), y(y), z(z) {}
  PoseMsg() {}
};
} // namespace fast::fr::messages
