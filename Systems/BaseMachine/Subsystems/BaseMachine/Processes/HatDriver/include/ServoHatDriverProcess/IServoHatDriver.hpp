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
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem {
    class IServoHatDriver {
       public:
        IServoHatDriver() = default;
        virtual ~IServoHatDriver() = default;
        virtual bool init(uint16_t address = 0) = 0;
        virtual std::string pretty() = 0;
        virtual bool setServoValue(uint16_t channel, uint16_t value) = 0;
    };
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem