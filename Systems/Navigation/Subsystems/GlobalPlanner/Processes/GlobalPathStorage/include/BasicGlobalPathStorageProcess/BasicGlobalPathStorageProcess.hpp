/**
 * @file BasicGlobalPathStorageProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <BaseGlobalPathStorageProcess.hpp>

namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem {
/**
 * @brief Minimal Implementation for a GlobalPathStorage Process
 *
 */
class BasicGlobalPathStorageProcess : public BaseGlobalPathStorageProcess {
public:
  BasicGlobalPathStorageProcess() : BaseGlobalPathStorageProcess() {}
  /**
   * @brief Update with recent timing data
   *
   * @param current_time_sec
   * @param delta_time_sec
   * @return true If update executed ok
   * @return false If update executed with some error
   */
  bool update(double current_time_sec, double delta_time_sec) override;

private:
};
} // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem