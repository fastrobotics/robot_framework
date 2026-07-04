add_executable(test_process_GlobalPathRoutePlanner
                 test_process_GlobalPathRoutePlanner.cpp)
  target_link_libraries(
    test_process_GlobalPathRoutePlanner GTest::gtest_main
    base_GlobalPathRoutePlannerProcess
  )

  gtest_discover_tests(test_process_GlobalPathRoutePlanner)