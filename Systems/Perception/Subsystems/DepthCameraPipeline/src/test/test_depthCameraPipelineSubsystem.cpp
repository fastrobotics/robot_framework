#include <gtest/gtest.h>
#include <stdio.h>

#include <DepthCameraPipelineSubsystem.hpp>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem;
#include <Infrastructure/Logger.hpp>

TEST(DepthCameraPipelineSubsystem, BasicTests) {
    DepthCameraPipelineSubsystem SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);
    fast::rf::Logger::logInfo(SUT.pretty());
    fast::rf::messages::SensorMsgs::PointCloudMsg pointCloud;
    std::string signalName = "sensor1";
    ASSERT_TRUE(SUT.addSignalToMonitor(signalName, "sensor_msgs/msg/PointCloud2", 20.0, 50.0));
    ASSERT_TRUE(SUT.newPointCloud(pointCloud, signalName));
    ASSERT_TRUE(SUT.update(0.0));
    auto readyToArm = SUT.get_ready_to_arm();
    ASSERT_GT(readyToArm.systemID, 0);
    ASSERT_GT(readyToArm.subsystemID, 0);
    ASSERT_EQ(readyToArm.processID, 0);
    ASSERT_FALSE(readyToArm.ready_to_arm);
    auto diagnostics = SUT.getDiagnostics();
    ASSERT_GT(diagnostics.size(), 0);
}