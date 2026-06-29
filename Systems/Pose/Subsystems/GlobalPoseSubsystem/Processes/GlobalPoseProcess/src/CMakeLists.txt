
add_library(base_global_pose_process STATIC BaseGlobalPoseProcess.cpp)
target_link_libraries(base_global_pose_process geometry_msgs sensor_msgs)
add_subdirectory(BasicGlobalPoseProcess)

if(BUILD_TESTING)

  add_executable(
    test_process_Global_Pose
    test/test_process_Global_Pose.cpp
  )
  target_link_libraries(
    test_process_Global_Pose
    GTest::gtest_main
    base_global_pose_process
    geometry_msgs
    sensor_msgs
  )


  gtest_discover_tests(test_process_Global_Pose)
endif()