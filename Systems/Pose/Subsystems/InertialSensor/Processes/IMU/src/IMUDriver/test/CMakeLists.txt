add_executable(test_driver_IMU test_driver_IMU.cpp)
target_link_libraries(
  test_driver_IMU
  GTest::gtest_main
  geometry_msgs
  sensor_msgs
  infrastructure_msgs
  base_IMUDriver
  mockIMUDriver)

gtest_discover_tests(test_driver_IMU)
