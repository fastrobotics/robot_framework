# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_process_TrajectoryController
               test_process_TrajectoryController.cpp)
target_link_libraries(test_process_TrajectoryController GTest::gtest_main
                      base_TrajectoryControllerProcess pid_Controller)

gtest_discover_tests(test_process_TrajectoryController)
