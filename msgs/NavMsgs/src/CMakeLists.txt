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