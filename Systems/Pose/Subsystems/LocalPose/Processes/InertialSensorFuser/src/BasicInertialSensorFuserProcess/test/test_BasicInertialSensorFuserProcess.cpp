

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicInertialSensorFuserProcess/BasicInertialSensorFuserProcess.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PoseSystem::LocalPoseSubsystem;

TEST(BasicInertialSensorFuserProcess, BasicTests) {
    BasicInertialSensorFuserProcess SUT;
    ASSERT_TRUE(SUT.init(1));
    ASSERT_TRUE(SUT.update(0.0));
    fast::rf::messages::SensorMsgs::ImuMsg sensor_imu_data;
    ASSERT_TRUE(SUT.new_imu_data(0, sensor_imu_data));
    auto diagnostics = SUT.get_diagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    for (auto diagnostic : diagnostics) {
        ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
    fast::rf::Logger::log_info(SUT.pretty());
}
TEST(BasicInertialSensorFuserProcess, FailureTests) {
    BasicInertialSensorFuserProcess SUT;

    {  // Unexpected number of IMU's
        ASSERT_FALSE(SUT.init(0));
        ASSERT_FALSE(SUT.init(2));
    }
    ASSERT_TRUE(SUT.init(1));
    {  // Unexpected IMU Message
        fast::rf::messages::SensorMsgs::ImuMsg sensor_imu_data;
        ASSERT_FALSE(SUT.new_imu_data(2, sensor_imu_data));
    }
}
TEST(BasicInertialSensorFuserProcess, PassThruTests) {
    BasicInertialSensorFuserProcess SUT;
    ASSERT_TRUE(SUT.init(1));
    ASSERT_TRUE(SUT.update(0.0));
    fast::rf::Logger::log_debug(SUT.pretty());
    fast::rf::messages::SensorMsgs::ImuMsg sensor_imu_data;
    sensor_imu_data.time_stamp = 1.0;
    ASSERT_TRUE(SUT.new_imu_data(0, sensor_imu_data));
    fast::rf::Logger::log_debug(SUT.pretty());
    fast::rf::messages::SensorMsgs::ImuMsg machine_inertial_data;
    ASSERT_TRUE(SUT.get_machine_inertial_data(machine_inertial_data));
    ASSERT_FLOAT_EQ(machine_inertial_data.time_stamp, 1.0);
    fast::rf::Logger::log_debug(SUT.pretty());
    ASSERT_FALSE(SUT.get_machine_inertial_data(machine_inertial_data));
    fast::rf::Logger::log_debug(SUT.pretty());
}