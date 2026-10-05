add_executable(test_depthCameraPipelineSubsystem
               test_depthCameraPipelineSubsystem.cpp)
target_link_libraries(test_depthCameraPipelineSubsystem GTest::gtest_main
                      infrastructure_msgs depthCameraPipelineSubsystem)

gtest_discover_tests(test_depthCameraPipelineSubsystem)
