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
    class MockServoHatDriver : public IServoHatDriver {
       public:
        MockServoHatDriver() = default;
        virtual ~MockServoHatDriver() = default;
        bool init(uint16_t address = 0) override;
        std::string pretty() override;
        bool setServoValue(uint16_t channel, uint16_t value) override;
    };
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem