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
        enum class Adafruit16ChServoHatConstant {
            MODE1 = 0x00,
            MODE2 = 0x01,
            SUBADR1 = 0x02,
            SUBADR2 = 0x03,
            SUBADR3 = 0x04,
            PRESCALE = 0xFE,
            LED0_ON_L = 0x06,
            LED0_ON_H = 0x07,
            LED0_OFF_L = 0x08,
            LED0_OFF_H = 0x09,
            ALL_LED_ON_L = 0xFA,
            ALL_LED_ON_H = 0xFB,
            ALL_LED_OFF_L = 0xFC,
            ALL_LED_OFF_H = 0xFD,
            RESTART = 0x80,
            SLEEP = 0x10,
            ALLCALL = 0x01,
            INVRT = 0x10,
            OUTDRV = 0x04,
        };

       public:
        ServoHatDriver() = default;
        virtual ~ServoHatDriver() = default;
        bool init(uin16_t address = 0x40) override;
        std::string pretty() override;
        bool setServoValue(uint16_t channel, uint16_t value);

       private:
        int servoHatFd{-1};
        void setPWMFreq(int freq);

        void setPWM(int pin_number, int on, int off);
    };
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem