
  add_executable(test_process_DriveExecutor test_process_DriveExecutor.cpp)
  target_link_libraries(
    test_process_DriveExecutor GTest::gtest_main base_DriveExecutorProcess
  )

  gtest_discover_tests(test_process_DriveExecutor)