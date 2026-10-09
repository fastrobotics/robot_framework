# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_depthCameraSensorCombiner
               test_depthCameraSensorCombiner.cpp)
target_link_libraries(test_depthCameraSensorCombiner GTest::gtest_main
                      DepthCameraPipelineSubsystem::combiner)

gtest_discover_tests(test_depthCameraSensorCombiner)

add_executable(test_process_SensorFuser test_process_SensorFuser.cpp)
target_link_libraries(
  test_process_SensorFuser GTest::gtest_main infrastructure_msgs
  DepthCameraPipelineSubsystem::base_SensorFuserProcess)

gtest_discover_tests(test_process_SensorFuser)
