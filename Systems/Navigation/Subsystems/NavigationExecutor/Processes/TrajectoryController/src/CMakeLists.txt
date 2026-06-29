add_library(base_TrajectoryControllerProcess STATIC BaseTrajectoryControllerProcess.cpp)
#target_link_libraries(base_TrajectoryControllerProcess geometry_msgs sensor_msgs)
add_subdirectory(BasicTrajectoryControllerProcess)

if(BUILD_TESTING)
  add_executable(
    test_process_TrajectoryController
    test/test_process_TrajectoryController.cpp
  )
  target_link_libraries(
    test_process_TrajectoryController
    GTest::gtest_main
    base_TrajectoryControllerProcess
    #geometry_msgs
    #sensor_msgs
  )


  gtest_discover_tests(test_process_TrajectoryController)
endif()