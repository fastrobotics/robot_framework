# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_process_FeatureDetector test_process_FeatureDetector.cpp)
target_link_libraries(test_process_FeatureDetector GTest::gtest_main
                      infrastructure_msgs base_FeatureDetectorProcess)

gtest_discover_tests(test_process_FeatureDetector)
