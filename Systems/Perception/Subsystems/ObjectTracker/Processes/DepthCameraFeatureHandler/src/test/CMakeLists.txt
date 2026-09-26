# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_process_DepthCameraFeatureHandler
               test_process_DepthCameraFeatureHandler.cpp)
target_link_libraries(test_process_DepthCameraFeatureHandler GTest::gtest_main
                      infrastructure_msgs base_DepthCameraFeatureHandlerProcess)

gtest_discover_tests(test_process_DepthCameraFeatureHandler)
