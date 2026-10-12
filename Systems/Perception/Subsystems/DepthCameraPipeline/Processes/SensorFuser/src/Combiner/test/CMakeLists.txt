add_executable(test_depthCameraSensorCombiner
               test_depthCameraSensorCombiner.cpp)
target_link_libraries(test_depthCameraSensorCombiner GTest::gtest_main
                      DepthCameraPipelineSubsystem::combiner)

gtest_discover_tests(test_depthCameraSensorCombiner)
