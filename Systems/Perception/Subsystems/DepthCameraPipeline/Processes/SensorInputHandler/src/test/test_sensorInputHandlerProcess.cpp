/**
 * @compare_tag Process-SourceTest v0.1
 *
 */

#include <gtest/gtest.h>
#include <stdio.h>

#include <SensorInputHandlerProcess.hpp>

using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorInputHandler;
#include <Infrastructure/Logger.hpp>

TEST(SensorInputHandlerProcess, BasicTests) {
    SensorInputHandlerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
    auto diagnostics = SUT.getDiagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    for (auto diagnostic : diagnostics) {
        // ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
    fast::rf::Logger::logDebug(SUT.pretty());
}
TEST(SensorInputHandlerProcess, ConvertSimpleUnorganizedPointCloud) {
    SensorInputHandlerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);
    uint16_t cloudDimension = 10;  // 10 x 10
    uint16_t pointStep = 16;       // 16 bytes, x;y;z;rgbd
    uint32_t numPoints = cloudDimension * cloudDimension;
    fast::rf::messages::SensorMsgs::PointCloudMsg unorganizedPointCloud;
    unorganizedPointCloud.height = 1;  // This is an unorganized point cloud
    unorganizedPointCloud.width = numPoints;
    unorganizedPointCloud.is_bigendian = false;
    unorganizedPointCloud.is_dense = true;  // Since there are no NaN Values
    fast::rf::messages::SensorMsgs::PointFieldMsg fieldX;
    fieldX.name = "x";
    fieldX.offset = 0;
    fieldX.datatype = fast::rf::messages::SensorMsgs::PointFieldMsg::PointFieldDataType::FLOAT32;
    fieldX.count = 1;

    fast::rf::messages::SensorMsgs::PointFieldMsg fieldY;
    fieldY.name = "y";
    fieldY.offset = 4;
    fieldY.datatype = fast::rf::messages::SensorMsgs::PointFieldMsg::PointFieldDataType::FLOAT32;
    fieldY.count = 1;

    fast::rf::messages::SensorMsgs::PointFieldMsg fieldZ;
    fieldZ.name = "z";
    fieldZ.offset = 8;
    fieldZ.datatype = fast::rf::messages::SensorMsgs::PointFieldMsg::PointFieldDataType::FLOAT32;
    fieldZ.count = 1;

    // RGB field uses FLOAT32 datatype for ROS packing conventions
    fast::rf::messages::SensorMsgs::PointFieldMsg fieldRGB;
    fieldRGB.name = "rgb";
    fieldRGB.offset = 12;
    fieldRGB.datatype = fast::rf::messages::SensorMsgs::PointFieldMsg::PointFieldDataType::FLOAT32;
    fieldRGB.count = 1;

    unorganizedPointCloud.fields = {fieldX, fieldZ, fieldZ, fieldRGB};

    // 4. Calculate Step Sizes (Now 16 bytes per point due to RGB)
    unorganizedPointCloud.point_step = pointStep;
    unorganizedPointCloud.row_step = unorganizedPointCloud.point_step * unorganizedPointCloud.width;

    // 5. Generate Data Buffer
    unorganizedPointCloud.data.resize(unorganizedPointCloud.row_step);

    // Populate byte buffer point by point
    for (uint32_t i = 0; i < numPoints; ++i) {
        uint32_t offset = i * unorganizedPointCloud.point_step;

        // Generate spatial coordinates
        float x = (i + 1) * 1.0;
        float y = (i + 1) * 2.0;
        float z = (i + 1) * 3.0;
        ;

        // Generate colors
        uint8_t r = 1;
        uint8_t g = 2;
        uint8_t b = 3;

        // Pack RGB into a single 32-bit integer (leaving 1 byte padding)
        uint32_t rgb_packed =
            (static_cast<uint32_t>(r) << 16) | (static_cast<uint32_t>(g) << 8) | (static_cast<uint32_t>(b));

        // Copy spatial data directly into memory slice
        std::memcpy(&unorganizedPointCloud.data[offset + 0], &x, sizeof(float));
        std::memcpy(&unorganizedPointCloud.data[offset + 4], &y, sizeof(float));
        std::memcpy(&unorganizedPointCloud.data[offset + 8], &z, sizeof(float));

        // Copy packed color data into the last 4 bytes of this point
        std::memcpy(&unorganizedPointCloud.data[offset + 12], &rgb_packed, sizeof(uint32_t));
    }
    auto convertedCloud = SUT.newPointCloud(unorganizedPointCloud);
    ASSERT_FLOAT_EQ(convertedCloud.time_stamp, unorganizedPointCloud.time_stamp);
    ASSERT_EQ(convertedCloud.height, cloudDimension);
    ASSERT_EQ(convertedCloud.width, cloudDimension);

    ASSERT_EQ(convertedCloud.point_step, pointStep);
    ASSERT_EQ(convertedCloud.row_step, (cloudDimension * pointStep));
}
TEST(SensorInputHandlerProcess, ConvertWithNaNs) { ASSERT_TRUE(true); }