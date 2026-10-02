# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_process_SensorInputHandler
               test_process_SensorInputHandler.cpp)
target_link_libraries(
  test_process_SensorInputHandler GTest::gtest_main infrastructure_msgs
  DepthCameraPipeline::base_SensorInputHandlerProcess)

gtest_discover_tests(test_process_SensorInputHandler)
