if(BUILD_TESTING)

  add_executable(test_basic_SensorInputHandlerProcess
                 test_BasicSensorInputHandlerProcess.cpp)
  target_link_libraries(test_basic_SensorInputHandlerProcess GTest::gtest_main
                        DepthCameraPipeline::basic_SensorInputHandlerProcess)

  gtest_discover_tests(test_basic_SensorInputHandlerProcess)
endif()
