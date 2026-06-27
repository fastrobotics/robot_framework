# Test: {{cookiecutter.Package}}Msgs::{{cookiecutter.Message}}Msg
add_executable(
  test_msgs_{{cookiecutter.Package}}Msgs_{{cookiecutter.Message}}Msg
  test/test_msgs_{{cookiecutter.Package}}Msgs_{{cookiecutter.Message}}Msg.cpp
)
target_link_libraries(
  test_msgs_{{cookiecutter.Package}}Msgs_{{cookiecutter.Message}}Msg
  GTest::gtest_main
)

gtest_discover_tests(test_msgs_{{cookiecutter.Package}}Msgs_{{cookiecutter.Message}}Msg)