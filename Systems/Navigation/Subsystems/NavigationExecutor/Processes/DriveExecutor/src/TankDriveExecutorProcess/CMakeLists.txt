
add_library(TankDriveExecutorProcess STATIC TankDriveExecutorProcess.cpp)
target_link_libraries(TankDriveExecutorProcess PUBLIC base_DriveExecutorProcess)
target_include_directories(TankDriveExecutorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

if(BUILD_TESTING)

  add_executable(test_TankDriveExecutorConversion
                 test/test_TankDriveExecutorConversion.cpp)
  target_link_libraries(test_TankDriveExecutorConversion GTest::gtest_main
                        TankDriveExecutorProcess geometry_msgs)

  gtest_discover_tests(test_TankDriveExecutorConversion)

  add_executable(test_TankDriveExecutorProcess
                 test/test_TankDriveExecutorProcess.cpp)
  target_link_libraries(test_TankDriveExecutorProcess GTest::gtest_main
                        TankDriveExecutorProcess geometry_msgs)

  gtest_discover_tests(test_TankDriveExecutorProcess)
endif()
