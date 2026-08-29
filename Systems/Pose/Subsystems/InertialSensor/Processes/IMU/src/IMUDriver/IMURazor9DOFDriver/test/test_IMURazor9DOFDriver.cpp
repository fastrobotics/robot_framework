

#include <gtest/gtest.h>
#include <stdio.h>

#include <IMUDriver/IMURazor9DOFDriver/IMURazor9DOFDriver.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU;

TEST(IMURazor9DOFDriver, InterfaceTests) {
    IMURazor9DOFDriver SUT;
    ASSERT_FALSE(SUT.init(""));  // Won't be able to initialize as it's dependent on a Serial Port.
    fast::rf::Logger::logInfo(SUT.pretty());

    ASSERT_FALSE(SUT.update(0.1));  // Won't be able to update as it's dependent on a Serial Port
}
TEST(IMURazor9DOFDriver, PacketParsing) {
    IMURazor9DOFDriver SUT;
    auto packet =
        SUT.parse("$58530, 0.02, 0.15, -1.00, -0.91, -0.55, -0.12, 56.11, 16.35, -58.66, 3.06, 188.93, 341.81, 73.75");
    ASSERT_TRUE(packet.ok);
    auto sensor_msg = SUT.convert(packet);
    ASSERT_NE(sensor_msg.imu_msg.linear_acceleration.x, 0.0);
    ASSERT_NE(sensor_msg.magnetic_field_msg.magnetic_field.x, 0.0);

    // Bad Packets
    {  // No prefix
        ASSERT_FALSE(
            SUT.parse(
                   "58530, 0.02, 0.15, -1.00, -0.91, -0.55, -0.12, 56.11, 16.35, -58.66, 3.06, 188.93, 341.81, 73.75")
                .ok);
    }
    {  // Not enough Tokens
        ASSERT_FALSE(
            SUT.parse("$58530, 0.02, 0.15, -1.00, -0.91, -0.55, -0.12, 56.11, 16.35, -58.66, 3.06, 188.93, 341.81").ok);
    }
    {  // Too many tokens
        ASSERT_FALSE(SUT.parse("$58530, 0.02, 0.15, -1.00, -0.91, -0.55, -0.12, 56.11, 16.35, -58.66, 3.06, 188.93, "
                               "341.81,1.234,5.678")
                         .ok);
    }
    {  // Odd String in Data
        ASSERT_FALSE(SUT.parse("$58530, BAD_DATA, 0.15, -1.00, -0.91, -0.55, -0.12, 56.11, 16.35, -58.66, 3.06, "
                               "188.93, 341.81, 73.75")
                         .ok);
    }
}