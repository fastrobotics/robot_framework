

#include <gtest/gtest.h>
#include <stdio.h>

#include <IMUDriver/BaseIMUDriver.hpp>
#include <IMUDriver/IIMUDriver.hpp>
#include <IMUDriver/MockIMUDriver.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PoseSystem::InertialSensorSubsystem;
class TestIMUDriverInterface : public IIMUDriver {
   public:
    bool init([[maybe_unused]] IIMUDriver::IMUDevice device) { return true; }
    std::string pretty() { return ""; }
    fast::rf::messages::SensorMsgs::ImuMsg get_imu_data() {
        fast::rf::messages::SensorMsgs::ImuMsg data;
        return data;
    }
    bool update([[maybe_unused]] double current_time) { return true; }
};

TEST(TestIIMUDriverInterface, InterfaceTests) {
    TestIMUDriverInterface SUT;
    ASSERT_TRUE(SUT.init(IIMUDriver::IMUDevice::MOCK_IMU));
    ASSERT_EQ(SUT.pretty().size(), 0);
    ASSERT_LT(SUT.get_imu_data().time_stamp, 0.0);
    ASSERT_TRUE(SUT.update(0.0));
}
class TestBaseIMUDriver : public BaseIMUDriver {
   public:
    bool init(IIMUDriver::IMUDevice device) { return BaseIMUDriver::init(device); }
    std::string pretty() { return BaseIMUDriver::pretty(); }
};
TEST(TestBaseIMUDriver, BasicAssertions) {
    TestBaseIMUDriver SUT;
    ASSERT_TRUE(SUT.init(IIMUDriver::IMUDevice::MOCK_IMU));
    ASSERT_GT(SUT.pretty().size(), 0);
    ASSERT_LT(SUT.get_imu_data().time_stamp, 0.0);
}

TEST(TestIMUMockDriver, BasicTests) {
    MockIMUDriver SUT;
    ASSERT_TRUE(SUT.init(IIMUDriver::IMUDevice::MOCK_IMU));
    ASSERT_GT(SUT.pretty().size(), 0);
    ASSERT_GT(SUT.get_imu_data().time_stamp, 0.0);
}