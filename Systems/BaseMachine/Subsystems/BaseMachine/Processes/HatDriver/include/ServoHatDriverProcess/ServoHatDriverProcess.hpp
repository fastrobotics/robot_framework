/**
 *
 */
#pragma once

#include <BaseHatDriverProcess.hpp>

namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem {
    /**
     * @brief Servo Hat Driver Process
     *
     */
    class ServoHatDriverProcess : public BaseHatDriverProcess {
       public:
        ServoHatDriverProcess() : BaseHatDriverProcess() {}

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
         * @param delta_time_sec
         * @return true If update executed ok
         * @return false If update executed with some error
         */
        bool update(double current_time_sec, double delta_time_sec) override;

       private:
    };
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem