#include <ServoHatDriverProcess/ServoHatDriver.hpp>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem {
    bool ServoHatDriver::init() { return true; }
    std::string ServoHatDriver::pretty() {
        std::string str;
        str = "---Mock Servo Hat Driver---";
        return str;
    }
}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem