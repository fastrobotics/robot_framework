# Test: {{cookiecutter.Package}}Msgs::{{cookiecutter.Service}}Srv
add_executable(
  test_msgs_{{cookiecutter.Package}}Msgs_{{cookiecutter.Service}}Srv
  test_msgs_{{cookiecutter.Package}}Msgs_{{cookiecutter.Service}}Srv.cpp)
target_link_libraries(
  test_msgs_{{cookiecutter.Package}}Msgs_{{cookiecutter.Service}}Srv
  GTest::gtest_main)

gtest_discover_tests(
  test_msgs_{{cookiecutter.Package}}Msgs_{{cookiecutter.Service}}Srv)
