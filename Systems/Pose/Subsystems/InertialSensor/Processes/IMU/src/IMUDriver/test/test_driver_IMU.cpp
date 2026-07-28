

#include <gtest/gtest.h>
#include <stdio.h>

#include <IMUDriver/BaseIMUDriver.hpp>
#include <IMUDriver/IIMUDriver.hpp>
#include <IMUDriver/MockIMUDriver.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PoseSystem::InertialSensorSubsystem;
class TestIMUDriverInterface : public IIMUDriver {
   public:
    bool init() { return true; }
    std::string pretty() { return ""; }
    fast::rf::messages::SensorMsgs::ImuMsg get_imu_data() {
        fast::rf::messages::SensorMsgs::ImuMsg data;
        return data;
    }
    fast::rf::messages::SensorMsgs::MagneticFieldMsg get_magnetic_data() {
        fast::rf::messages::SensorMsgs::MagneticFieldMsg data;
        return data;
    }
    bool update([[maybe_unused]] double current_time) { return true; }
};

TEST(TestIIMUDriverInterface, InterfaceTests) {
    TestIMUDriverInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.pretty().size(), 0);
    ASSERT_LT(SUT.get_imu_data().time_stamp, 0.0);
    ASSERT_LT(SUT.get_magnetic_data().time_stamp, 0.0);
    ASSERT_TRUE(SUT.update(0.1));
}
class TestBaseIMUDriver : public BaseIMUDriver {
   public:
    bool init() { return BaseIMUDriver::init(IIMUDriver::IMUDevice::MOCK_IMU); }
    std::string pretty() { return BaseIMUDriver::pretty(); }
    bool update(double current_time) { return BaseIMUDriver::update(current_time); }
};
TEST(TestBaseIMUDriver, BasicAssertions) {
    TestBaseIMUDriver SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.1));
    ASSERT_GT(SUT.pretty().size(), 0);
    ASSERT_LT(SUT.get_imu_data().time_stamp, 0.0);
    ASSERT_LT(SUT.get_magnetic_data().time_stamp, 0.0);
}

TEST(TestIMUMockDriver, BasicTests) {
    MockIMUDriver SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_GT(SUT.pretty().size(), 0);
    ASSERT_GT(SUT.get_imu_data().time_stamp, 0.0);
    ASSERT_GT(SUT.get_magnetic_data().time_stamp, 0.0);
}