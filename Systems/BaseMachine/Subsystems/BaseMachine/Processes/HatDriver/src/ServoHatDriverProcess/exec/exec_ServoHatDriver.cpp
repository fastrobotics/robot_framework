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
    printf("-r Reset all Channels.\n");
    printf("-c Channel Number.\n");
    printf("-m Mode: ramp,direct.\n");
    printf("-v Value to Set.\n");
}
int main(int argc, char* argv[]) {
    fast::rf::Logger::init(fast::rf::Level::DEBUG, "ServoHatDriver");
    bool reset = false;
    int channel = 0;
    int value = 0;
    std::string mode = "direct";  // default
    for (;;) {
        switch (getopt(argc, argv,
                       "rc:m:v:h"))  // note the colon (:) to indicate that 'b' has a parameter and
                                     // is not a switch
        {
            case 'r':
                reset = true;
                break;
            case 'c':
                channel = atoi(optarg);
                continue;
            case 'm':
                mode = optarg;
                if (mode == "ramp") {
                    break;
                } else {
                    continue;
                };
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
        fast::rf::Logger::log_error("Unable to Initialize Driver.  Exiting!");
        return 1;
    }
    fast::rf::Logger::log_info(driver->pretty());
    if (reset == true) {
        for (uint8_t ch = 0; ch < 16; ++ch) {
            driver->setServoValue(ch, IServoHatDriver::MED_SERVO_VALUE);
        }
        delete driver;
        return 0;
    } else if (mode == "direct") {
    } else if (mode == "ramp") {
        value = IServoHatDriver::MED_SERVO_VALUE;
    } else {
        fast::rf::Logger::log_error("Mode: " + mode + " Not Supported.  Exiting!");
        delete driver;
        return 1;
    }
    double delta_time_sec = 0.02;
    bool direction = true;

    while (true) {
        usleep(delta_time_sec * 1000000.0);
        if (mode == "ramp") {
            if (value >= IServoHatDriver::MAX_SERVO_VALUE) {
                direction = false;
            } else if (value <= IServoHatDriver::MIN_SERVO_VALUE) {
                direction = true;
            }
            if (direction == true) {
                value += 1;
            } else {
                value -= 1;
            }
        } else if (mode == "direct") {  // Default, nothing to do here
        }
        driver->setServoValue(channel, value);
        if (mode == "direct") {
            fast::rf::Logger::log_notice("Holding for 3 Seconds");
            usleep(3.0 * 1000000.0);  // Holdfor 3 seconds
            driver->setServoValue(channel, IServoHatDriver::MED_SERVO_VALUE);
            fast::rf::Logger::log_notice("Done, Exiting.");
            delete driver;
            return 0;
        }
    }
    delete driver;
    return 0;
}
