if(BUILD_TESTING)

  add_executable(test_basic_InertialSensorFuserProcess
                 test_BasicInertialSensorFuserProcess.cpp)
  target_link_libraries(test_basic_InertialSensorFuserProcess
                        GTest::gtest_main basic_InertialSensorFuserProcess)

  gtest_discover_tests(test_basic_InertialSensorFuserProcess)
endif()
