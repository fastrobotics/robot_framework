# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_process_HatDriver test_process_HatDriver.cpp)
target_link_libraries(test_process_HatDriver GTest::gtest_main
                      base_HatDriverProcess)

gtest_discover_tests(test_process_HatDriver)
