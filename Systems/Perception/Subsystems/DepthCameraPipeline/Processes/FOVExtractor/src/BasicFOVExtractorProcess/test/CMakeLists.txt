if(BUILD_TESTING)

  add_executable(test_basic_FOVExtractorProcess
                 test_BasicFOVExtractorProcess.cpp)
  target_link_libraries(test_basic_FOVExtractorProcess GTest::gtest_main
                        basic_FOVExtractorProcess)

  gtest_discover_tests(test_basic_FOVExtractorProcess)
endif()
