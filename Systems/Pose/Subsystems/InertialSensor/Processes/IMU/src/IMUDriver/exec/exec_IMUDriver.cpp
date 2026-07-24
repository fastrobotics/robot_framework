// LCOV_EXCL_START
// No way to unit test this, this is a sample executive driver

#include <unistd.h>

#include <IMUDriver/IIMUDriver.hpp>
#include <IMUDriver/IMUSYDTM151Driver/IMUSYDTM151Driver.hpp>
#include <IMUDriver/MockIMUDriver.hpp>
#include <Infrastructure/Logger.hpp>
#include <RobotFrameworkDefinitions.hpp>

using namespace fast::rf::PoseSystem::InertialSensorSubsystem;
void printHelp() {
    printf("Tester for IMU Driver\n");
    printf("-h This Menu.\n");
    printf("-d Driver Version: 1-Mock 2-SYDTM151\n");
}
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    fast::rf::Logger::init(fast::rf::Level::DEBUG, "IMUDriver");

    double delta_time_sec = 0.02;
    uint8_t driver_version = 0;
    IIMUDriver* driver;

    for (;;) {
        switch (getopt(argc, argv,
                       "d:h"))  // note the colon (:) to indicate that 'b' has a parameter and
                                // is not a switch
        {
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
    bool status = false;
    switch (driver_version) {
        case 1:
            driver = new MockIMUDriver();
            status = driver->init(IIMUDriver::IMUDevice::MOCK_IMU);
            if (status == false) {
                return 1;
            }
            break;
        case 2:
            driver = new IMUSYDTM151Driver();
            status = driver->init(IIMUDriver::IMUDevice::SYDTM151_IMU);
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
    while (true) {
        usleep(delta_time_sec * 1000000.0);
        fast::rf::Logger::log_info(driver->pretty());
    }
    delete driver;
    return 0;
}
// LCOV_EXCL_STOP