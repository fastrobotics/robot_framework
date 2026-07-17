if(BUILD_TESTING)

  # Test: InfrastructureMsgs::DiagnosticMsg
  add_executable(test_msgs_InfrastructureMsgs_DiagnosticMsg
                 test_msgs_InfrastructureMsgs_DiagnosticMsg.cpp)
  target_link_libraries(test_msgs_InfrastructureMsgs_DiagnosticMsg
                        GTest::gtest_main)

  gtest_discover_tests(test_msgs_InfrastructureMsgs_DiagnosticMsg)

  # Test: InfrastructureMsgs::ReadyToArmStatusMsg
  add_executable(test_msgs_InfrastructureMsgs_ReadyToArmStatusMsg
                 test_msgs_InfrastructureMsgs_ReadyToArmStatusMsg.cpp)
  target_link_libraries(test_msgs_InfrastructureMsgs_ReadyToArmStatusMsg
                        GTest::gtest_main)

  gtest_discover_tests(test_msgs_InfrastructureMsgs_ReadyToArmStatusMsg)

  # Test: InfrastructureMsgs::ArmCommandMsg
  add_executable(test_msgs_InfrastructureMsgs_ArmCommandMsg
                 test_msgs_InfrastructureMsgs_ArmCommandMsg.cpp)
  target_link_libraries(test_msgs_InfrastructureMsgs_ArmCommandMsg
                        GTest::gtest_main)

  gtest_discover_tests(test_msgs_InfrastructureMsgs_ArmCommandMsg)

  # Test: InfrastructureMsgs::ArmStateChangeSrv
  add_executable(test_msgs_InfrastructureMsgs_ArmStateChangeSrv
                 test_msgs_InfrastructureMsgs_ArmStateChangeSrv.cpp)
  target_link_libraries(test_msgs_InfrastructureMsgs_ArmStateChangeSrv
                        GTest::gtest_main)

  gtest_discover_tests(test_msgs_InfrastructureMsgs_ArmStateChangeSrv)
endif()
