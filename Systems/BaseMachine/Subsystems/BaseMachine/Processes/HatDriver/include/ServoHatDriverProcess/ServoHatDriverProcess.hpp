/**
 * @file ServoHatDriverProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-09-01
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-BasicHeader
 */
#pragma once

#include <BaseHatDriverProcess.hpp>
#ifdef ARCHITECTURE_ARMV7L
#include <ServoHatDriverProcess/ServoHatDriver.hpp>
#else
#include <ServoHatDriverProcess/MockServoHatDriver.hpp>
#endif

namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver {
    /**
     * @brief Servo Hat Driver Process
     *
     */
    class ServoHatDriverProcess : public BaseHatDriverProcess {
       public:
        static constexpr uint8_t MAX_CHANNEL_COUNT = 16;  //!< Max number of channels on a Servo Hat
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
         * @return true If update executed ok
         * @return false If update executed with some error
         */
        bool update(double current_time_sec) override;

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
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver