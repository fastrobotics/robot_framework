# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_baseSensorInputHandler test_baseSensorInputHandler.cpp)
target_link_libraries(
  test_baseSensorInputHandler GTest::gtest_main infrastructure_msgs
  DepthCameraPipeline::base_SensorInputHandlerProcess)

gtest_discover_tests(test_baseSensorInputHandler)

add_executable(test_sensorInputHandlerProcess
               test_sensorInputHandlerProcess.cpp)
target_link_libraries(test_sensorInputHandlerProcess GTest::gtest_main
                      DepthCameraPipeline::sensorInputHandlerProcess)

gtest_discover_tests(test_sensorInputHandlerProcess)
