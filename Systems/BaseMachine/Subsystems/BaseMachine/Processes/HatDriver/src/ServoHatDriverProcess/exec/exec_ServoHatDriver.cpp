#ifdef ARCHITECTURE_ARMV7L
#include <ServoHatDriverProcess/ServoHatDriver.hpp>
#else
#include <ServoHatDriverProcess/MockServoHatDriver.hpp>
#endif
#include <Infrastructure/Logger.hpp>
#include <RobotFrameworkDefinitions.hpp>
using namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem;
void printHelp() {
    printf("Tester for Servo Hat Driver\n");
    printf("-h This Menu.\n");
    printf("-r Reset all Channels.\n");
    printf("-c Channel Number.\n");
    printf("-m Mode: ramp,direct.\n");
    printf("-v Value to Set.\n");
}
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    fast::rf::Logger::init(fast::rf::Level::DEBUG, "ServoHatDriver");

    IServoHatDriver* driver;
#ifdef ARCHITECTURE_ARMV7L
    driver = new ServoHatDriver();
#else
    driver = new MockServoHatDriver();
#endif
    if (driver->init() == false) {
        fast::rf::Logger::log_error("Unable to Initialize Driver.");
    }
    fast::rf::Logger::log_info(driver->pretty());
    delete driver;
    return 0;
}
