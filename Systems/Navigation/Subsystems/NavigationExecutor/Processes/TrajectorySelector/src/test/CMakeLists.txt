add_executable(test_process_TrajectorySelector
                test_process_TrajectorySelector.cpp)
target_link_libraries(
test_process_TrajectorySelector GTest::gtest_main
base_TrajectorySelectorProcess
)

gtest_discover_tests(test_process_TrajectorySelector)