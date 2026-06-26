
add_library(basic_global_pose_process STATIC BasicGlobalPoseProcess.cpp)
target_link_libraries(basic_global_pose_process base_global_pose_process geometry_msgs sensor_msgs)

add_executable(
  test_basic_global_pose_process
  test/test_Basic_Global_Pose_Process.cpp
)
target_link_libraries(
  test_basic_global_pose_process
  GTest::gtest_main
  basic_global_pose_process
  geometry_msgs
  sensor_msgs
)


gtest_discover_tests(test_basic_global_pose_process)