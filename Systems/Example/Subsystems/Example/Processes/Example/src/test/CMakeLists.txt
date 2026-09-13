# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_process_Example test_process_Example.cpp)
target_link_libraries(test_process_Example GTest::gtest_main
                      infrastructure_msgs base_ExampleProcess)

gtest_discover_tests(test_process_Example)
