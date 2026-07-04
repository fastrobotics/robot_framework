add_executable(test_process_FreeSpacePlanner
                 test_process_FreeSpacePlanner.cpp)
  target_link_libraries(
    test_process_FreeSpacePlanner GTest::gtest_main
    base_FreeSpacePlannerProcess
  )

  gtest_discover_tests(test_process_FreeSpacePlanner)