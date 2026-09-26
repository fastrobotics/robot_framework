# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_process_ObjectEstimator test_process_ObjectEstimator.cpp)
target_link_libraries(test_process_ObjectEstimator GTest::gtest_main
                      infrastructure_msgs base_ObjectEstimatorProcess)

gtest_discover_tests(test_process_ObjectEstimator)
