add_executable(test_process_IMU test_process_IMU.cpp)
target_link_libraries(test_process_IMU GTest::gtest_main infrastructure_msgs
                      imuProcess)

gtest_discover_tests(test_process_IMU)
