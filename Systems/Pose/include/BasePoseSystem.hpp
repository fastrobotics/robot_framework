#pragma once
#include <IPoseSystem.hpp>
#include <PoseMsg.hpp>

namespace fast::rf::PoseSystem {
class BasePoseSystem : public IPoseSystem {
public:
  /**
   * @brief Get the global pose object
   *
   * @return fast::rf::messages::Pose::PoseMsg
   */
  fast::rf::messages::Pose::PoseMsg get_global_pose() override {
    return global_pose_;
  }
  /**
   * @brief Get the local pose object
   *
   * @return fast::rf::messages::Pose::PoseMsg
   */
  fast::rf::messages::Pose::PoseMsg get_local_pose() override {
    return local_pose_;
  }

protected:
  /**
   * @brief
   *
   * @param current_time_sec
   * @param delta_time_sec
   * @return true
   * @return false
   */
  bool base_update(double current_time_sec, double delta_time_sec);

  double current_time_sec_{-1.0};
  fast::rf::messages::Pose::PoseMsg global_pose_;
  fast::rf::messages::Pose::PoseMsg local_pose_;
};
} // namespace fast::rf::PoseSystem