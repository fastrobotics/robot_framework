# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_baseSensorHealthMonitor test_baseSensorHealthMonitor.cpp)
target_link_libraries(
  test_baseSensorHealthMonitor GTest::gtest_main infrastructure_msgs
  DepthCameraPipelineSubsystem::base_SensorHealthMonitorProcess)

gtest_discover_tests(test_baseSensorHealthMonitor)

add_executable(test_sensorHealthMonitorProcess
               test_sensorHealthMonitorProcess.cpp)
target_link_libraries(test_sensorHealthMonitorProcess GTest::gtest_main
                      DepthCameraPipelineSubsystem::sensorHealthMonitorProcess)

gtest_discover_tests(test_sensorHealthMonitorProcess)
