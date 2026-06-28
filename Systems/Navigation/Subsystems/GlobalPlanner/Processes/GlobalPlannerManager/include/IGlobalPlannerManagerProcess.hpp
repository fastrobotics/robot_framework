/**
 * @file IGlobalPlannerManagerProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem {
/**
 * @brief Interface for the GlobalPlannerManager Process
 *
 */
class IGlobalPlannerManagerProcess {
public:
  IGlobalPlannerManagerProcess() = default;
  virtual ~IGlobalPlannerManagerProcess() = default;
  /**
   * @brief Generic Update function
   *
   * @param current_time_sec Current time stamp
   * @param delta_time_sec Difference in time between previous iterations
   * @return true If the process updated ok
   * @return false If the process did not update ok
   */
  virtual bool update(double current_time_sec, double delta_time_sec) = 0;
  
};
} // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem