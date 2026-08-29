

#include <gtest/gtest.h>
#include <stdio.h>

#include <IMUDriver/IMUSYDTM151Driver/IMUSYDTM151Driver.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU;

TEST(IMUSYDTM151Driver, InterfaceTests) {
    IMUSYDTM151Driver SUT;
    ASSERT_FALSE(SUT.init(""));  // Won't be able to initialize as it's dependent on a Serial Port.
    fast::rf::Logger::logInfo(SUT.pretty());
    ASSERT_FALSE(SUT.update(0.1));  // Won't be able to update as it's dependent on a Serial Port
}
TEST(IMURazor9DOFDriver, PacketParsing) {
    IMUSYDTM151Driver SUT;
    ASSERT_FALSE(SUT.init(""));  // Won't be able to initialize as it's dependent on a Serial Port.
    BaseIMUDriver::DataPacket data_packet;
    data_packet.ok = true;
    auto sensor_msg = SUT.convert(data_packet);
    ASSERT_FLOAT_EQ(sensor_msg.imu_msg.linear_acceleration.x, 0.0);
    ASSERT_FLOAT_EQ(sensor_msg.magnetic_field_msg.magnetic_field.x, 0.0);
}