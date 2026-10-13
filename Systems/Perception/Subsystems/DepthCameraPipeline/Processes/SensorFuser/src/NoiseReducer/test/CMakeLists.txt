add_executable(test_depthCameraSensorNoiseReducer
               test_depthCameraSensorNoiseReducer.cpp)
target_link_libraries(
  test_depthCameraSensorNoiseReducer
  PRIVATE GTest::gtest_main DepthCameraPipelineSubsystem::noiseReducerCPU)
if(ARCHITECTURE_JETSONNANO)
  target_link_libraries(test_depthCameraSensorNoiseReducer
                        PRIVATE DepthCameraPipelineSubsystem::noiseReducerGPU)
endif()

gtest_discover_tests(test_depthCameraSensorNoiseReducer)
