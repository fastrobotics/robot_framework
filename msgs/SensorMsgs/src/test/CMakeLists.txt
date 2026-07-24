# Test: SensorMsgs::GlobalPositionSensorMsg
add_executable(test_SensorMsgs_GlobalPositionSensorMsg
               test_SensorMsgs_GlobalPositionSensorMsg.cpp)
target_link_libraries(test_SensorMsgs_GlobalPositionSensorMsg GTest::gtest_main
                      standard_msgs)

gtest_discover_tests(test_SensorMsgs_GlobalPositionSensorMsg)

# Test: SensorMsgs::JoyMsg
add_executable(test_msgs_SensorMsgs_JoyMsg test_msgs_SensorMsgs_JoyMsg.cpp)
target_link_libraries(test_msgs_SensorMsgs_JoyMsg GTest::gtest_main)

gtest_discover_tests(test_msgs_SensorMsgs_JoyMsg)

# Test: SensorMsgs::ImuMsg
add_executable(test_msgs_SensorMsgs_ImuMsg test_msgs_SensorMsgs_ImuMsg.cpp)
target_link_libraries(test_msgs_SensorMsgs_ImuMsg GTest::gtest_main
                      standard_msgs geometry_msgs infrastructure_msgs logger)

gtest_discover_tests(test_msgs_SensorMsgs_ImuMsg)
