add_library(basic_DriveExecutorProcess STATIC BasicDriveExecutorProcess.cpp)
target_link_libraries(basic_DriveExecutorProcess base_DriveExecutorProcess)

if(BUILD_TESTING)

  add_executable(test_basic_DriveExecutorProcess
                 test/test_BasicDriveExecutorProcess.cpp)
  target_link_libraries(test_basic_DriveExecutorProcess GTest::gtest_main
                        basic_DriveExecutorProcess)

  gtest_discover_tests(test_basic_DriveExecutorProcess)
endif()
