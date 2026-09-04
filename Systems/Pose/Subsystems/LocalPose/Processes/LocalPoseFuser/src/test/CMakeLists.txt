# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_process_LocalPoseFuser test_process_LocalPoseFuser.cpp)
target_link_libraries(test_process_LocalPoseFuser GTest::gtest_main
                      infrastructure_msgs base_LocalPoseFuserProcess)

gtest_discover_tests(test_process_LocalPoseFuser)
