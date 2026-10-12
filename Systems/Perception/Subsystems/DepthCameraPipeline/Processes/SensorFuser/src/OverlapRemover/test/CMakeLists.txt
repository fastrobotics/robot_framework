add_executable(test_depthCameraSensorOverlapRemover
               test_depthCameraSensorOverlapRemover.cpp)
target_link_libraries(test_depthCameraSensorOverlapRemover GTest::gtest_main
                      DepthCameraPipelineSubsystem::overlapRemover)

gtest_discover_tests(test_depthCameraSensorOverlapRemover)
