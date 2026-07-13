add_executable(test_MockServoHatDriver test_MockServoHatDriver.cpp)
target_link_libraries(test_MockServoHatDriver GTest::gtest_main
                      infrastructure_msgs mockServoHatDriver)

gtest_discover_tests(test_MockServoHatDriver)

add_executable(test_ServoHatDriverProcess test_ServoHatDriverProcess.cpp)
target_link_libraries(test_ServoHatDriverProcess GTest::gtest_main
                      infrastructure_msgs servoHatDriverProcess)

gtest_discover_tests(test_ServoHatDriverProcess)
