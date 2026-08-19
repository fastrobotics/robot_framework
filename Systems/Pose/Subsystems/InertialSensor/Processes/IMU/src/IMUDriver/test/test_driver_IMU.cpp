

#include <gtest/gtest.h>
#include <stdio.h>

#include <IMUDriver/BaseIMUDriver.hpp>
#include <IMUDriver/IIMUDriver.hpp>
#include <IMUDriver/MockIMUDriver.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU;
class TestIMUDriverInterface : public IIMUDriver {
   public:
    bool init([[maybe_unused]] std::string device_name) { return true; }
    std::string pretty() { return ""; }
    bool get_imu_data(fast::rf::messages::SensorMsgs::ImuMsg& data) {
        fast::rf::messages::SensorMsgs::ImuMsg imu_data;
        data = imu_data;
        return true;
    }
    bool get_magnetic_data(fast::rf::messages::SensorMsgs::MagneticFieldMsg& data) {
        fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_data;
        data = magnetic_data;
        return true;
    }
    bool update([[maybe_unused]] double current_time) { return true; }

    double get_packet_dropped_rate() override { return 0.0; }

    double get_packet_rx_rate() override { return 0.0; }
};

TEST(TestIIMUDriverInterface, InterfaceTests) {
    TestIMUDriverInterface SUT;
    ASSERT_TRUE(SUT.init(""));
    ASSERT_EQ(SUT.pretty().size(), 0);

    ASSERT_TRUE(SUT.update(0.1));
    fast::rf::messages::SensorMsgs::ImuMsg imu_data;
    ASSERT_TRUE(SUT.get_imu_data(imu_data));
    ASSERT_LT(imu_data.time_stamp, 0.0);
    fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_data;
    ASSERT_TRUE(SUT.get_magnetic_data(magnetic_data));
    ASSERT_LT(magnetic_data.time_stamp, 0.0);
}
class TestBaseIMUDriver : public BaseIMUDriver {
   public:
    bool init(std::string device_name) { return BaseIMUDriver::init(IIMUDriver::IMUDevice::MOCK_IMU, device_name); }
    std::string pretty() { return BaseIMUDriver::pretty(); }
    bool update(double current_time) { return BaseIMUDriver::update(current_time); }
};
TEST(TestBaseIMUDriver, BasicAssertions) {
    TestBaseIMUDriver SUT;
    ASSERT_TRUE(SUT.init(""));
    ASSERT_TRUE(SUT.update(0.1));
    ASSERT_GT(SUT.pretty().size(), 0);
    fast::rf::messages::SensorMsgs::ImuMsg imu_data;
    ASSERT_FALSE(SUT.get_imu_data(imu_data));
    ASSERT_LT(imu_data.time_stamp, 0.0);
    fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_data;
    ASSERT_FALSE(SUT.get_magnetic_data(magnetic_data));
    ASSERT_LT(magnetic_data.time_stamp, 0.0);
}

TEST(TestIMUMockDriver, BasicTests) {
    MockIMUDriver SUT;
    ASSERT_TRUE(SUT.init(""));
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_GT(SUT.pretty().size(), 0);
    fast::rf::messages::SensorMsgs::ImuMsg imu_data;
    ASSERT_TRUE(SUT.get_imu_data(imu_data));
    ASSERT_GT(imu_data.time_stamp, 0.0);
    fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_data;
    ASSERT_TRUE(SUT.get_magnetic_data(magnetic_data));
    ASSERT_GT(magnetic_data.time_stamp, 0.0);
}