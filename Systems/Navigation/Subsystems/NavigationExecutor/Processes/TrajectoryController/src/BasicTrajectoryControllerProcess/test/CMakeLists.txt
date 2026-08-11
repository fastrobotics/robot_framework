add_executable(test_basic_TrajectoryControllerProcess
               test_BasicTrajectoryControllerProcess.cpp)
target_link_libraries(test_basic_TrajectoryControllerProcess GTest::gtest_main
                      basic_TrajectoryControllerProcess)

gtest_discover_tests(test_basic_TrajectoryControllerProcess)
