add_executable(test_process_ArmedStateManager
               test_process_ArmedStateManager.cpp)
target_link_libraries(test_process_ArmedStateManager GTest::gtest_main
                      infrastructure_msgs base_ArmedStateManagerProcess)

gtest_discover_tests(test_process_ArmedStateManager)
