# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_process_InertialSensorFuser
               test_process_InertialSensorFuser.cpp)
target_link_libraries(test_process_InertialSensorFuser GTest::gtest_main
                      infrastructure_msgs base_InertialSensorFuserProcess)

gtest_discover_tests(test_process_InertialSensorFuser)
