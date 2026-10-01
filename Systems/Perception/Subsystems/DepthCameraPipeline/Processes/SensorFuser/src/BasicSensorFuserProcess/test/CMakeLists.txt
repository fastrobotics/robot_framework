if(BUILD_TESTING)

  add_executable(test_basic_SensorFuserProcess test_BasicSensorFuserProcess.cpp)
  target_link_libraries(test_basic_SensorFuserProcess GTest::gtest_main
                        basic_SensorFuserProcess)

  gtest_discover_tests(test_basic_SensorFuserProcess)
endif()
