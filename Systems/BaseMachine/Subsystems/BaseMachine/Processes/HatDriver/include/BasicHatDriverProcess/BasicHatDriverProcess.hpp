/**
 * @file BasicHatDriverProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <BaseHatDriverProcess.hpp>

namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem {
    /**
     * @brief Minimal Implementation for a HatDriver Process
     *
     */
    class BasicHatDriverProcess : public BaseHatDriverProcess {
       public:
        BasicHatDriverProcess() : BaseHatDriverProcess() {}

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
         * @brief Human readable version of the object
         *
         * @return std::string
         */
        std::string pretty() override;

       private:
    };
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem