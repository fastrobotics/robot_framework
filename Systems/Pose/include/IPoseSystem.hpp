#pragma once
#include <PoseMsg.hpp>

namespace fast::rf::PoseSystem {
class IPoseSystem {
public:
  IPoseSystem() = default;
  virtual ~IPoseSystem() = default;
  /**
   * @brief
   *
   * @param current_time_sec
   * @param delta_time_sec
   * @return true
   * @return false
   */
  virtual bool update(double current_time_sec, double delta_time_sec) = 0;
  /**
   * @brief Get the global pose object
   *
   * @return fast::rf::messages::Pose::PoseMsg
   */
  virtual fast::rf::messages::Pose::PoseMsg get_global_pose() = 0;
  /**
   * @brief Get the local pose object
   *
   * @return fast::rf::messages::Pose::PoseMsg
   */
  virtual fast::rf::messages::Pose::PoseMsg get_local_pose() = 0;
};
} // namespace fast::rf::PoseSystem