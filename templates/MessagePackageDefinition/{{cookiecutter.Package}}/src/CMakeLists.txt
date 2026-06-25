add_executable(
  test_msgs_{{cookiecutter.Package}}
  test/test_msgs_{{cookiecutter.Package}}.cpp
)
target_link_libraries(
  test_msgs_{{cookiecutter.Package}}
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_msgs_{{cookiecutter.Package}})