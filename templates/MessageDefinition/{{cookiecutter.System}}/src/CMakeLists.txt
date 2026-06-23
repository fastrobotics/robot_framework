add_executable(
  test_msgs_{{cookiecutter.Message}}
  test/test_msgs_{{cookiecutter.Message}}.cpp
)
target_link_libraries(
  test_msgs_{{cookiecutter.Message}}
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_msgs_{{cookiecutter.Message}})