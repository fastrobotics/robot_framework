set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};/usr/share/cmake/geographiclib")
find_package(GeographicLib REQUIRED)

add_library(basic_global_pose_process STATIC BasicGlobalPoseProcess.cpp)
target_link_libraries(basic_global_pose_process base_global_pose_process
                      geometry_msgs sensor_msgs ${GeographicLib_LIBRARIES})
target_include_directories(basic_global_pose_process
                           PRIVATE ${GeographicLib_INCLUDE_DIRS})
target_compile_definitions(basic_global_pose_process
                           PRIVATE ${GeographicLib_DEFINITIONS})

if(BUILD_TESTING)

  add_executable(test_basic_global_pose_process
                 test/test_Basic_Global_Pose_Process.cpp)
  target_link_libraries(test_basic_global_pose_process GTest::gtest_main
                        basic_global_pose_process geometry_msgs sensor_msgs)

  gtest_discover_tests(test_basic_global_pose_process)
endif()
