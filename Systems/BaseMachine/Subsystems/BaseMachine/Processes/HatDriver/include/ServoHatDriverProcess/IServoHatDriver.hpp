/**
 * @file IServoHatDriver.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-11
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <cstdint>
#include <string>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver {
    /**
     * @brief Interface class for a generic Servo Hat
     *
     */

    class IServoHatDriver {
       public:
        static constexpr uint16_t MAX_SERVO_VALUE = 2000;  //!< Max Servo Value
        static constexpr uint16_t MED_SERVO_VALUE = 1500;  //!< Medium Servo Value
        static constexpr uint16_t MIN_SERVO_VALUE = 1000;  //!< Min Servo Value
        IServoHatDriver() = default;
        virtual ~IServoHatDriver() = default;
        /**
         * @brief Initialize the Hat with an address
         *
         * @param address
         * @return true
         * @return false
         */
        virtual bool init(uint16_t address = 0x40) = 0;
        /**
         * @brief Get a human readable string representing the status of the object
         *
         * @return std::string
         */
        virtual std::string pretty() = 0;
        /**
         * @brief Set the Servo Value at a Channel
         *
         * @param channel
         * @param value
         * @return true
         * @return false
         */
        virtual bool setServoValue(uint16_t channel, uint16_t value) = 0;
    };
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver