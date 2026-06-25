add_executable(
  test_msgs_Sensor
  test/test_msgs_Sensor.cpp
)
target_link_libraries(
  test_msgs_Sensor
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_msgs_Sensor)