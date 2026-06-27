add_executable(
  test_msgs_NavMsgs_GlobalPathRequestMsg
  test/test_msgs_NavMsgs_GlobalPathRequestMsg.cpp
)
target_link_libraries(
  test_msgs_NavMsgs_GlobalPathRequestMsg
  GTest::gtest_main
  geometry_msgs
)

include(GoogleTest)
gtest_discover_tests(test_msgs_NavMsgs_GlobalPathRequestMsg)

add_executable(
  test_msgs_NavMsgs_GlobalPathPlanningStatusEnum
  test/test_msgs_NavMsgs_GlobalPathPlanningStatusEnum.cpp
)
target_link_libraries(
  test_msgs_NavMsgs_GlobalPathPlanningStatusEnum
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_msgs_NavMsgs_GlobalPathPlanningStatusEnum)

add_executable(
  test_msgs_NavMsgs_GlobalPathResponseMsg
  test/test_msgs_NavMsgs_GlobalPathResponseMsg.cpp
)
target_link_libraries(
  test_msgs_NavMsgs_GlobalPathResponseMsg
  GTest::gtest_main
  geometry_msgs
)

include(GoogleTest)
gtest_discover_tests(test_msgs_NavMsgs_GlobalPathResponseMsg)