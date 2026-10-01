# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_process_FOVExtractor test_process_FOVExtractor.cpp)
target_link_libraries(test_process_FOVExtractor GTest::gtest_main
                      infrastructure_msgs base_FOVExtractorProcess)

gtest_discover_tests(test_process_FOVExtractor)
