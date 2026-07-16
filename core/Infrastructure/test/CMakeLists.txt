add_executable(test_Logger test_Logger.cpp)
target_link_libraries(test_Logger GTest::gtest_main logger infrastructure_msgs)
gtest_discover_tests(test_Logger)
