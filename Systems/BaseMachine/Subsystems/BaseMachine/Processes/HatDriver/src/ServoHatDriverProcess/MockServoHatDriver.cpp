#include <Infrastructure/Logger.hpp>
#include <ServoHatDriverProcess/MockServoHatDriver.hpp>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem {
    bool MockServoHatDriver::init([[maybe_unused]] uint16_t address) {
        fast::rf::Logger::log_info("Initializing Mock Servo Hat Driver at address: " + std::to_string(address));
        return true;
    }
    std::string MockServoHatDriver::pretty() {
        std::string str;
        str = "---Mock Servo Hat Driver---";
        return str;
    }
    bool MockServoHatDriver::setServoValue(uint16_t channel, uint16_t value) {
        fast::rf::Logger::log_info("I'm a Mock, setting Channel: " + std::to_string(channel) +
                                   " to: " + std::to_string(value));
        return true;
    }
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem