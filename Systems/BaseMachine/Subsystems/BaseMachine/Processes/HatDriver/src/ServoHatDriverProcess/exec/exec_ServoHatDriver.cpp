#ifdef ARCHITECTURE_ARMV7L
#include <ServoHatDriverProcess/ServoHatDriver.hpp>
#else
#include <ServoHatDriverProcess/MockServoHatDriver.hpp>
#endif
#include <unistd.h>

#include <Infrastructure/Logger.hpp>
#include <RobotFrameworkDefinitions.hpp>
using namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem;
void printHelp() {
    printf("Tester for Servo Hat Driver\n");
    printf("-h This Menu.\n");
    // printf("-r Reset all Channels.\n");
    printf("-c Channel Number.\n");
    // printf("-m Mode: ramp,direct.\n");
    printf("-v Value to Set.\n");
}
int main(int argc, char* argv[]) {
    fast::rf::Logger::init(fast::rf::Level::DEBUG, "ServoHatDriver");
    // bool reset = false;
    int channel = 0;
    int value = 0;
    std::string mode = "direct";  // default
    for (;;) {
        switch (getopt(argc, argv,
                       "rc:m:v:h"))  // note the colon (:) to indicate that 'b' has a parameter and
                                     // is not a switch
        {
            /*
            case 'r':
                reset = true;
                break;
            */
            case 'c':
                channel = atoi(optarg);
                continue;
                /*
            case 'm':
                mode = optarg;
                if (mode == "ramp") {
                    break;
                } else {
                    continue;
                };
            */
            case 'v':
                value = atoi(optarg);
                break;
            case '?':
                printHelp();
                return 0;
            case 'h':
                printHelp();
                return 0;
            default:
                printHelp();
                return 0;
        }

        break;
    }
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
    double delta_time_sec = 0.01;
    while (true) {
        fast::rf::Logger::log_debug("Running");
        usleep(delta_time_sec * 1000000.0);
        driver->setServoValue(channel, value);
    }
    delete driver;
    return 0;
}
