if(BUILD_TESTING)

  add_executable(test_basic_ExampleProcess test_BasicExampleProcess.cpp)
  target_link_libraries(test_basic_ExampleProcess GTest::gtest_main
                        basic_ExampleProcess)

  gtest_discover_tests(test_basic_ExampleProcess)
endif()
