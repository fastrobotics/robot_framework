if(BUILD_TESTING)

  add_executable(test_basic_LocalPoseFuserProcess
                 test_BasicLocalPoseFuserProcess.cpp)
  target_link_libraries(test_basic_LocalPoseFuserProcess
                        GTest::gtest_main basic_LocalPoseFuserProcess)

  gtest_discover_tests(test_basic_LocalPoseFuserProcess)
endif()
