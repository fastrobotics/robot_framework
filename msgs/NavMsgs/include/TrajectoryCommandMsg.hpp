/**
 * @file TrajectoryCommandMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <GeometryMsgs.hpp>

#include <vector>
using namespace fast::rf::messages;
namespace fast::rf::messages::NavMsgs {
/**
 * @brief Data Structure for encoding Trajectory Command
 *
 */
struct TrajectoryCommandMsg {
  std::vector<GeometryMsgs::TwistWithCovarianceMsg>
      cmd_twists; //!< List of Command Twists with tolerance
  TrajectoryCommandMsg() {}
};
} // namespace fast::rf::messages::NavMsgs
