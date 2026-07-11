/**
 * @file ServoHatDriver.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-11
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <wiringPiI2C.h>

#include <ServoHatDriverProcess/IServoHatDriver.hpp>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem {
    class ServoHatDriver : public IServoHatDriver {
       public:
        ServoHatDriver() = default;
        virtual ~ServoHatDriver() = default;
        bool init() override;
        std::string pretty() override;
    };
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem