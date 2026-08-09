add_executable(test_PIDController test_PID_Controller.cpp)
target_link_libraries(test_PIDController GTest::gtest_main pid_Controller
                      logger)

gtest_discover_tests(test_PIDController)
