# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_process_SensorFuser test_process_SensorFuser.cpp)
target_link_libraries(test_process_SensorFuser GTest::gtest_main
                      infrastructure_msgs base_SensorFuserProcess)

gtest_discover_tests(test_process_SensorFuser)
