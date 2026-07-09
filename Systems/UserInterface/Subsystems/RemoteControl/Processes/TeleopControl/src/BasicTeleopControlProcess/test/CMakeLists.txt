add_executable(test_TwistComputer test_TwistComputer.cpp)
target_link_libraries(test_TwistComputer GTest::gtest_main
                      remoteControlTwistComputer geometry_msgs sensor_msgs)
gtest_discover_tests(test_TwistComputer)

add_executable(test_basic_TeleopControlProcess
               test_BasicTeleopControlProcess.cpp)
target_link_libraries(test_basic_TeleopControlProcess GTest::gtest_main
                      basic_TeleopControlProcess)
gtest_discover_tests(test_basic_TeleopControlProcess)
