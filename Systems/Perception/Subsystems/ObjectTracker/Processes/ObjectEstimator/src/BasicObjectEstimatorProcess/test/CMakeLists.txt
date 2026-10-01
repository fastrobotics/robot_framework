if(BUILD_TESTING)

  add_executable(test_basic_ObjectEstimatorProcess
                 test_BasicObjectEstimatorProcess.cpp)
  target_link_libraries(test_basic_ObjectEstimatorProcess GTest::gtest_main
                        basic_ObjectEstimatorProcess)

  gtest_discover_tests(test_basic_ObjectEstimatorProcess)
endif()
