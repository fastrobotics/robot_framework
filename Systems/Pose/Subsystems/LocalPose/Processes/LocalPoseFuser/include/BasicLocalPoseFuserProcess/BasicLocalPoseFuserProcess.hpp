/**
 * @file BasicLocalPoseFuserProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <BaseLocalPoseFuserProcess.hpp>

namespace fast::rf::PoseSystem::LocalPoseSubsystem {
    /**
     * @brief Minimal Implementation for a LocalPoseFuser Process
     *
     */
    class BasicLocalPoseFuserProcess : public BaseLocalPoseFuserProcess {
       public:
        BasicLocalPoseFuserProcess() : BaseLocalPoseFuserProcess() {}

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
         * @param current_time_sec
         * @return true If update executed ok
         * @return false If update executed with some error
         */
        bool update(double current_time_sec) override;

        /**
         * @brief Human readable status of object
         *
         * @return std::string
         */
        std::string pretty() override;

       private:
    };
}  // namespace fast::rf::PoseSystem::LocalPoseSubsystem