/**
 * @file BaseFreeSpacePlannerProcess.hpp
 * @author yDavid Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IFreeSpacePlannerProcess.hpp>
namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem {
/**
 * @brief Base FreeSpacePlanner Process
  @details Concrete FreeSpacePlanner Processes should derive from this
 *
 */
class BaseFreeSpacePlannerProcess : public IFreeSpacePlannerProcess {
   public:
    /**
     * @brief Construct a new Base FreeSpacePlanner Process object
     *
     */
    BaseFreeSpacePlannerProcess() {}
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