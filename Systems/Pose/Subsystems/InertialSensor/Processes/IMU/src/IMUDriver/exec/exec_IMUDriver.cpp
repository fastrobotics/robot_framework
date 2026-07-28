// LCOV_EXCL_START
// No way to unit test this, this is a sample executive driver

#include <unistd.h>

#include <IMUDriver/IIMUDriver.hpp>
#include <IMUDriver/IMURazor9DOFDriver/IMURazor9DOFDriver.hpp>
#include <IMUDriver/IMUSYDTM151Driver/IMUSYDTM151Driver.hpp>
#include <IMUDriver/MockIMUDriver.hpp>
#include <Infrastructure/Logger.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <chrono>

using namespace fast::rf::PoseSystem::InertialSensorSubsystem;
void printHelp() {
    printf("Tester for IMU Driver\n");
    printf("-h This Menu.\n");
    printf("-l Logger Level (2:DEBUG ->7: FATAL)\n");
    printf("-d Driver Version: 1-Mock 2-SYDTM151 3-Razor9DOF\n");
}
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    double delta_time_sec = 0.0001;
    uint8_t logger_level = 2;
    uint8_t driver_version = 0;
    IIMUDriver* driver;

    for (;;) {
        switch (getopt(argc, argv, "l:d:h")) {
            case 'l':
                logger_level = atoi(optarg);
                continue;
            case 'd':
                driver_version = atoi(optarg);
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
    if ((logger_level < (uint8_t)fast::rf::Level::DEBUG) || (logger_level > (uint8_t)fast::rf::Level::FATAL)) {
        printf("Logger Level Threshold %d Invalid!", logger_level);
        return 1;
    }

    fast::rf::Logger::init((fast::rf::Level)logger_level, "IMUDriver");
    bool status = false;
    switch (driver_version) {
        case 1:
            driver = new MockIMUDriver();
            status = driver->init();
            if (status == false) {
                return 1;
            }
            break;
        case 2:
            driver = new IMUSYDTM151Driver();
            status = driver->init();
            if (status == false) {
                return 1;
            }
            break;
        case 3:
            driver = new IMURazor9DOFDriver();
            status = driver->init();
            if (status == false) {
                return 1;
            }
            break;
        default:
            fast::rf::Logger::log_error("Unsupported Driver Version!");
            return 1;
    }

    if (status == false) {
        fast::rf::Logger::log_error("Unable to initialize IMU Driver!");
        return 1;
    }
    double current_time = 0.0;
    double timer = 0.0;
    double time_loop = 1.0;
    while (true) {
        if (driver->update(current_time) == false) {
            fast::rf::Logger::log_warn("Unable to Update Driver!");
        }
        timer += delta_time_sec;
        if (timer >= time_loop) {
            timer = 0.0;
            fast::rf::Logger::log_info(driver->pretty());
        }

        usleep(delta_time_sec * 1000000.0);
        current_time += delta_time_sec;
    }
    delete driver;
    return 0;
}
// LCOV_EXCL_STOP