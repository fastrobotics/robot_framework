if(BUILD_TESTING)

  add_executable(test_basic_ArmedStateManagerProcess
                 test_BasicArmedStateManagerProcess.cpp)
  target_link_libraries(test_basic_ArmedStateManagerProcess GTest::gtest_main
                        basic_ArmedStateManagerProcess)

  gtest_discover_tests(test_basic_ArmedStateManagerProcess)
endif()
