add_executable(
  test_msgs_Geometry
  test/test_msgs_Geometry.cpp
)
target_link_libraries(
  test_msgs_Geometry
  GTest::gtest_main
  standard_msg
)

include(GoogleTest)
gtest_discover_tests(test_msgs_Geometry)