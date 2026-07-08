add_executable(test_process_TeleopControl test_process_TeleopControl.cpp)
target_link_libraries(test_process_TeleopControl GTest::gtest_main
                      base_TeleopControlProcess)

gtest_discover_tests(test_process_TeleopControl)
