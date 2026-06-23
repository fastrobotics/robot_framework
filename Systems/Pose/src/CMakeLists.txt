add_executable(
  test_system_Pose
  test/test_system_Pose.cpp
)
target_link_libraries(
  test_system_Pose
  GTest::gtest_main
  pose_msg
)

include(GoogleTest)
gtest_discover_tests(test_system_Pose)