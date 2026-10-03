add_executable(test_signalMonitor test_signalMonitor.cpp)
target_link_libraries(test_signalMonitor GTest::gtest_main infrastructure_msgs
                      logger signalMonitor)

gtest_discover_tests(test_signalMonitor)
