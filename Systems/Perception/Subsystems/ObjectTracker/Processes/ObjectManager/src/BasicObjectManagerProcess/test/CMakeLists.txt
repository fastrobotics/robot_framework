if(BUILD_TESTING)

  add_executable(test_basic_ObjectManagerProcess
                 test_BasicObjectManagerProcess.cpp)
  target_link_libraries(test_basic_ObjectManagerProcess GTest::gtest_main
                        basic_ObjectManagerProcess)

  gtest_discover_tests(test_basic_ObjectManagerProcess)
endif()
