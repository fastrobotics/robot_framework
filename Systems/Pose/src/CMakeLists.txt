add_library(base_pose_system STATIC BasePoseSystem.cpp)
target_link_libraries(base_pose_system geometry_msgs)
add_library(dummy_pose_system STATIC DummyPoseSystem/DummyPoseSystem.cpp)
target_link_libraries(dummy_pose_system base_pose_system)

if(BUILD_TESTING)

  add_executable(test_system_Pose test/test_system_Pose.cpp)
  target_link_libraries(test_system_Pose GTest::gtest_main geometry_msgs
                        pose_system_interface base_pose_system)

  gtest_discover_tests(test_system_Pose)

  add_executable(test_DummyPoseSystem test/test_DummyPoseSystem.cpp)
  target_link_libraries(test_DummyPoseSystem GTest::gtest_main geometry_msgs
                        dummy_pose_system)

  gtest_discover_tests(test_DummyPoseSystem)
endif()
