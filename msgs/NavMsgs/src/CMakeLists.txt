if(BUILD_TESTING)
  # Test: NavMsgs::GlobalPathRequestMsg
  add_executable(
    test_msgs_NavMsgs_GlobalPathRequestMsg
    test/test_msgs_NavMsgs_GlobalPathRequestMsg.cpp
  )
  target_link_libraries(
    test_msgs_NavMsgs_GlobalPathRequestMsg
    GTest::gtest_main
    geometry_msgs
  )

  gtest_discover_tests(test_msgs_NavMsgs_GlobalPathRequestMsg)

  # Test: NavMsgs::GlobalPathPlanningStatusEnum
  add_executable(
    test_msgs_NavMsgs_GlobalPathPlanningStatusEnum
    test/test_msgs_NavMsgs_GlobalPathPlanningStatusEnum.cpp
  )
  target_link_libraries(
    test_msgs_NavMsgs_GlobalPathPlanningStatusEnum
    GTest::gtest_main
  )

  gtest_discover_tests(test_msgs_NavMsgs_GlobalPathPlanningStatusEnum)

  # Test: NavMsgs::GlobalPathPlanningStateMsg
  add_executable(
    test_msgs_NavMsgs_GlobalPathPlanningState
    test/test_msgs_NavMsgs_GlobalPathPlanningState.cpp
  )
  target_link_libraries(
    test_msgs_NavMsgs_GlobalPathPlanningState
    GTest::gtest_main
  )

  gtest_discover_tests(test_msgs_NavMsgs_GlobalPathPlanningState)

  # Test: NavMsgs::GlobalPathResponseMsg
  add_executable(
    test_msgs_NavMsgs_GlobalPathResponseMsg
    test/test_msgs_NavMsgs_GlobalPathResponseMsg.cpp
  )
  target_link_libraries(
    test_msgs_NavMsgs_GlobalPathResponseMsg
    GTest::gtest_main
    geometry_msgs
  )

  gtest_discover_tests(test_msgs_NavMsgs_GlobalPathResponseMsg)

  # Test: NavMsgs::GlobalPathCommandMsg
  add_executable(
    test_msgs_NavMsgs_GlobalPathCommandMsg
    test/test_msgs_NavMsgs_GlobalPathCommandMsg.cpp
  )
  target_link_libraries(
    test_msgs_NavMsgs_GlobalPathCommandMsg
    GTest::gtest_main
    geometry_msgs
  )
  gtest_discover_tests(test_msgs_NavMsgs_GlobalPathCommandMsg)


  # Test: NavMsgs::GlobalPathPlanningStatusEnum
  add_executable(
    test_msgs_NavMsgs_GlobalPathCommandStatusEnum
    test/test_msgs_NavMsgs_GlobalPathCommandStatusEnum.cpp
  )
  target_link_libraries(
    test_msgs_NavMsgs_GlobalPathCommandStatusEnum
    GTest::gtest_main
  )

  gtest_discover_tests(test_msgs_NavMsgs_GlobalPathCommandStatusEnum)

  # Test: NavMsgs::GlobalPathCommandStateMsg
  add_executable(
    test_msgs_NavMsgs_GlobalPathCommandStateMsg
    test/test_msgs_NavMsgs_GlobalPathCommandStateMsg.cpp
  )
  target_link_libraries(
    test_msgs_NavMsgs_GlobalPathCommandStateMsg
    GTest::gtest_main
  )

  gtest_discover_tests(test_msgs_NavMsgs_GlobalPathCommandStateMsg)

  # Test: NavMsgs::TrajectoryCommandMsg
  add_executable(
    test_msgs_NavMsgs_TrajectoryCommandMsg
    test/test_msgs_NavMsgs_TrajectoryCommandMsg.cpp
  )
  target_link_libraries(
    test_msgs_NavMsgs_TrajectoryCommandMsg
    GTest::gtest_main
    geometry_msgs
  )

  gtest_discover_tests(test_msgs_NavMsgs_TrajectoryCommandMsg)
endif()