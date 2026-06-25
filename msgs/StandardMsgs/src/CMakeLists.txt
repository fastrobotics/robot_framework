add_executable(
  test_msgs_Standard
  test/test_msgs_Standard.cpp
)
target_link_libraries(
  test_msgs_Standard
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_msgs_Standard)