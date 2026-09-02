/**
 * @compare_tag Process-BasicSourceTest v0.1
 *
 */

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicLocalPoseFuserProcess/BasicLocalPoseFuserProcess.hpp>
#include <Infrastructure/Logger.hpp>
using namespace fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser;

TEST(BasicLocalPoseFuserProcess, BasicTests) {
    BasicLocalPoseFuserProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));

    ASSERT_FALSE(SUT.get_ready_to_arm().ready_to_arm);

    fast::rf::messages::SensorMsgs::ImuMsg machine_inertial_data;
    ASSERT_TRUE(SUT.new_machine_inertial_data(machine_inertial_data));
    ASSERT_TRUE(SUT.update(1.0));
    fast::rf::Logger::logDebug(SUT.pretty());
    auto diagnostics = SUT.getDiagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    for (auto diagnostic : diagnostics) {
        ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
}
TEST(BasicLocalPoseFuserProcess, BasicInterfaceTests) {
    BasicLocalPoseFuserProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);

    fast::rf::messages::SensorMsgs::ImuMsg machine_inertial_data;
    machine_inertial_data.time_stamp = 0.5;
    machine_inertial_data.angular_velocity.z = 1.0;
    ASSERT_TRUE(SUT.new_machine_inertial_data(machine_inertial_data));
    ASSERT_TRUE(SUT.update(1.0));
    fast::rf::Logger::logDebug(SUT.pretty());
    fast::rf::messages::GeometryMsgs::OdomMsg local_pose;
    fast::rf::messages::GeometryMsgs::AccelWithCovarianceMsg angular_acc;
    ASSERT_TRUE(SUT.get_local_pose(local_pose, angular_acc));
    ASSERT_FLOAT_EQ(machine_inertial_data.angular_velocity.z, local_pose.twist.twist.angular.z);
    ASSERT_GT(angular_acc.time_stamp, 0.0);
}
