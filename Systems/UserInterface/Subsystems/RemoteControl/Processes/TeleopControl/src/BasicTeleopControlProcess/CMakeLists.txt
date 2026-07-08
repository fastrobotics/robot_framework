add_library(basic_TeleopControlProcess STATIC BasicTeleopControlProcess.cpp)
target_link_libraries(basic_TeleopControlProcess base_TeleopControlProcess)

if(BUILD_TESTING)

  add_executable(test_basic_TeleopControlProcess
                 test/test_BasicTeleopControlProcess.cpp)
  target_link_libraries(test_basic_TeleopControlProcess GTest::gtest_main
                        basic_TeleopControlProcess)

  gtest_discover_tests(test_basic_TeleopControlProcess)
endif()
