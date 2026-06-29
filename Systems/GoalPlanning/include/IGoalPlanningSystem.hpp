/**
 * @file IGoalPlanningSystem.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

namespace fast::rf::GoalPlanningSystem {
/**
 * @brief Interface for the GoalPlanning System
 *
 */
class IGoalPlanningSystem {
   public:
    IGoalPlanningSystem() = default;
    virtual ~IGoalPlanningSystem() = default;
};
}  // namespace fast::rf::GoalPlanningSystem