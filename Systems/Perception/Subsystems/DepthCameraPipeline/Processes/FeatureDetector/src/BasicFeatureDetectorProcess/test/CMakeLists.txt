if(BUILD_TESTING)

  add_executable(test_basic_FeatureDetectorProcess
                 test_BasicFeatureDetectorProcess.cpp)
  target_link_libraries(test_basic_FeatureDetectorProcess GTest::gtest_main
                        basic_FeatureDetectorProcess)

  gtest_discover_tests(test_basic_FeatureDetectorProcess)
endif()
