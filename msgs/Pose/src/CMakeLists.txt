add_executable(
  test_msgs_Pose
  test/test_msgs_Pose.cpp
)
target_link_libraries(
  test_msgs_Pose
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_msgs_Pose)