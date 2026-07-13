/**
 * @file MockServoHatDriver.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-11
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <ServoHatDriverProcess/IServoHatDriver.hpp>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem {
    /**
     * @brief Mock Servo Hat Driver.  Does nothing, but can executed onx86_64.
     *
     */
    class MockServoHatDriver : public IServoHatDriver {
       public:
        MockServoHatDriver() = default;
        virtual ~MockServoHatDriver() = default;
        /**
         * @brief Initialize the fake object
         *
         * @param address
         * @return true
         * @return false
         */
        bool init(uint16_t address = 0) override;
        /**
         * @brief Get a human readable string of the object
         *
         * @return std::string
         */
        std::string pretty() override;
        /**
         * @brief Set fake data
         *
         * @param channel
         * @param value
         * @return true
         * @return false
         */
        bool setServoValue(uint16_t channel, uint16_t value) override;
    };
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem