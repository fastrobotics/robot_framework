/**
 *
 */
#pragma once

#include <BaseHatDriverProcess.hpp>
#ifdef ARCHITECTURE_ARMV7L
#include <ServoHatDriverProcess/ServoHatDriver.hpp>
#else
#include <ServoHatDriverProcess/MockServoHatDriver.hpp>
#endif

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

        /**
         * @brief Set the Servo Value on a Channel
         *
         * @param channel
         * @param value
         * @return true
         * @return false
         */
        bool setServoValue(uint16_t channel, uint16_t value);

        /**
         * @brief Human readable string of the object
         *
         * @return std::string
         */
        std::string pretty();

       private:
        IServoHatDriver* driver;  //!< Will be either a Mock ServoHatDriver if executed on x86_64 or a real
                                  //!< ServoHatDriver if executed on armv7l.
    };
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem