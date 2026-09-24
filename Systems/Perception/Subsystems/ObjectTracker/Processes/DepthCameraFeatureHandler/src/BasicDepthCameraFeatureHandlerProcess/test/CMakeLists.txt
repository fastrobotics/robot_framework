if(BUILD_TESTING)

  add_executable(test_basic_DepthCameraFeatureHandlerProcess
                 test_BasicDepthCameraFeatureHandlerProcess.cpp)
  target_link_libraries(
    test_basic_DepthCameraFeatureHandlerProcess GTest::gtest_main
    basic_DepthCameraFeatureHandlerProcess)

  gtest_discover_tests(test_basic_DepthCameraFeatureHandlerProcess)
endif()
