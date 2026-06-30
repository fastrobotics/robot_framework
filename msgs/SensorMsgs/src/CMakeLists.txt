if(BUILD_TESTING)
  add_executable(test_SensorMsgs_GlobalPositionSensorMsg
                 test/test_SensorMsgs_GlobalPositionSensorMsg.cpp)
  target_link_libraries(test_SensorMsgs_GlobalPositionSensorMsg
                        GTest::gtest_main standard_msgs)

  gtest_discover_tests(test_SensorMsgs_GlobalPositionSensorMsg)
endif()
