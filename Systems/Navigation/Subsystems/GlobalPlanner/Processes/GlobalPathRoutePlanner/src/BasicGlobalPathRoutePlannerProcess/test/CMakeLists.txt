  add_executable(test_basic_GlobalPathRoutePlannerProcess
                 test_BasicGlobalPathRoutePlannerProcess.cpp)
  target_link_libraries(test_basic_GlobalPathRoutePlannerProcess
                        GTest::gtest_main basic_GlobalPathRoutePlannerProcess)

  gtest_discover_tests(test_basic_GlobalPathRoutePlannerProcess)