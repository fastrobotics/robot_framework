#include <ServoHatDriverProcess/ServoHatDriver.hpp>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem {
    bool ServoHatDriver::init(uint16_t address) {
        servoHatFd = wiringPiI2CSetup(address);
        resetAllPWM(0, 0);

        wiringPiI2CWriteReg8(servoHatFd, (int)Adafruit16ChServoHatConstant::MODE2,
                             (int)Adafruit16ChServoHatConstant::OUTDRV);
        wiringPiI2CWriteReg8(servoHatFd, (int)Adafruit16ChServoHatConstant::MODE1,
                             (int)Adafruit16ChServoHatConstant::ALLCALL);

        int mode1 = wiringPiI2CReadReg8(servoHatFd, (int)Adafruit16ChServoHatConstant::MODE1);
        if (mode1 < 0) {
            return false;
        }
        mode1 = mode1 & ~(int)Adafruit16ChServoHatConstant::SLEEP;
        if (mode1 < 0) {
            return false;
        }
        wiringPiI2CWriteReg8(servoHatFd, (int)Adafruit16ChServoHatConstant::MODE1, mode1);

        setPWMFreq(60);
        return true;
    }
    std::string ServoHatDriver::pretty() {
        std::string str;
        str = "---Servo Hat Driver---";
        return str;
    }
    bool setServoValue(uint16_t channel, uint16_t value) {
        fast::rf::Logger::log_info("C: " + std::to_string(channel) + " V: " + std::to_string(value));
        return false;
    }
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem