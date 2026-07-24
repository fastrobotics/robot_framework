

#include <gtest/gtest.h>
#include <stdio.h>

#include <IMUDriver/IMURazor9DOFDriver/IMURazor9DOFDriver.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PoseSystem::InertialSensorSubsystem;

TEST(IMURazor9DOFDriver, InterfaceTests) {
    IMURazor9DOFDriver SUT;
    ASSERT_FALSE(SUT.init(
        IIMUDriver::IMUDevice::RAZOR9DOF_IMU));  // Won't be able to initialize as it's dependent on a Serial Port.
    fast::rf::Logger::log_info(SUT.pretty());
}
TEST(IMURazor9DOFDriver, PacketParsing) {
    IMURazor9DOFDriver SUT;
    auto packet = SUT.parse("$85281, 0.08, 0.16, -1.01, -0.06, -0.12, 0.00, 60.47, -6.90, -75.32");
    ASSERT_TRUE(packet.ok);
}