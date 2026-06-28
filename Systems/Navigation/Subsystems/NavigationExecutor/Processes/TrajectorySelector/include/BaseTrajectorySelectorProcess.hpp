/**
 * @file BaseTrajectorySelectorProcess.hpp
 * @author yDavid Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <ITrajectorySelectorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
/**
 * @brief Base TrajectorySelector Process
  @details Concrete TrajectorySelector Processes should derive from this
 *
 */
class BaseTrajectorySelectorProcess : public ITrajectorySelectorProcess {

public:
  /**
   * @brief Construct a new Base TrajectorySelector Process object
   *
   */
  BaseTrajectorySelectorProcess() {}
  /**
   * @brief Update the base object
   *
   * @param current_time_sec
   * @param delta_time_sec
   * @return true If ok
   * @return false If not ok
   */
  bool base_update(double current_time_sec,
                   double delta_time_sec); //!< Base function to update

protected:
  double current_time_sec_{-1.0};    //!< Current system time
};
} // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem