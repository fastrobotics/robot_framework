/**
 * @file BaseGlobalPathRoutePlannerProcess.hpp
 * @author yDavid Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IGlobalPathRoutePlannerProcess.hpp>
namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem {
/**
 * @brief Base GlobalPathRoutePlanner Process
  @details Concrete GlobalPathRoutePlanner Processes should derive from this
 *
 */
class BaseGlobalPathRoutePlannerProcess : public IGlobalPathRoutePlannerProcess {
   public:
    /**
     * @brief Construct a new Base GlobalPathRoutePlanner Process object
     *
     */
    BaseGlobalPathRoutePlannerProcess() {}
    /**
     * @brief Update the base object
     *
     * @param current_time_sec
     * @param delta_time_sec
     * @return true If ok
     * @return false If not ok
     */
    bool base_update(double current_time_sec,
                     double delta_time_sec);  //!< Base function to update

   protected:
    double current_time_sec_{-1.0};  //!< Current system time
};
}  // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem