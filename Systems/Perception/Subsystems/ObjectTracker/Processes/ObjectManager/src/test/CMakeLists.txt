# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_process_ObjectManager test_process_ObjectManager.cpp)
target_link_libraries(test_process_ObjectManager GTest::gtest_main
                      infrastructure_msgs base_ObjectManagerProcess)

gtest_discover_tests(test_process_ObjectManager)
