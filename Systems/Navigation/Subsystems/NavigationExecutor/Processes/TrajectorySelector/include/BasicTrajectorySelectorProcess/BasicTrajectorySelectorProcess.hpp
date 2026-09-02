/**
 * @file BasicTrajectorySelectorProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-BasicHeader v0.1
 */
#pragma once

#include <BaseTrajectorySelectorProcess.hpp>

namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectorySelector {
    /**
     * @brief Minimal implementation for a TrajectorySelector Process
     *
     */
    class BasicTrajectorySelectorProcess : public BaseTrajectorySelectorProcess {
       public:
        BasicTrajectorySelectorProcess() : BaseTrajectorySelectorProcess() {}

        /**
         * @brief Initialize the Object
         *
         * @return true
         * @return false
         */
        bool init() override;

        /**
         * @brief Update with recent timing data
         *
         * @param currentTimeSec
         * @return true If update executed ok
         * @return false If update executed with some error
         */
        bool update(double currentTimeSec) override;

        /**
         * @brief Human readable string for the process.  Called by concrete object.
         *
         * @return std::string
         */
        std::string pretty() override;

       private:
    };
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectorySelector
