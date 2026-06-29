
add_library(base_DriveExecutorProcess STATIC BaseDriveExecutorProcess.cpp)
target_link_libraries(base_DriveExecutorProcess geometry_msgs)
add_subdirectory(BasicDriveExecutorProcess)
add_subdirectory(TankDriveExecutorProcess)

if(BUILD_TESTING)

  add_executable(
    test_process_DriveExecutor
    test/test_process_DriveExecutor.cpp
  )
  target_link_libraries(
    test_process_DriveExecutor
    GTest::gtest_main
    base_DriveExecutorProcess
    #geometry_msgs
    #sensor_msgs
  )


  gtest_discover_tests(test_process_DriveExecutor)
endif()

