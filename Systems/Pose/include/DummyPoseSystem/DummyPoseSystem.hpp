/**
 * @file DummyPoseSystem.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-24
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <BasePoseSystem.hpp>

namespace fast::rf::PoseSystem {
class DummyPoseSystem : public BasePoseSystem {
public:
  /**
   * @brief
   *
   * @param current_time_sec
   * @param delta_time_sec
   * @return true
   * @return false
   */
  bool update(double current_time_sec, double delta_time_sec) override;
};
} // namespace fast::rf::PoseSystem