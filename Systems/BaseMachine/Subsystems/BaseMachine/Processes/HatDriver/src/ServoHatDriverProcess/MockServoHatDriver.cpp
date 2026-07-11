#include <ServoHatDriverProcess/MockServoHatDriver.hpp>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem {
    bool MockServoHatDriver::init() { return true; }
    std::string MockServoHatDriver::pretty() {
        std::string str;
        str = "---Mock Servo Hat Driver---";
        return str;
    }
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem