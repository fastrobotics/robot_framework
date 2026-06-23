add_executable(
  test_system_{{cookiecutter.System}}
  test/test_system_{{cookiecutter.System}}.cpp
)
target_link_libraries(
  test_system_{{cookiecutter.System}}
  GTest::gtest_main
  pose_msg
)

include(GoogleTest)
gtest_discover_tests(test_system_{{cookiecutter.System}})
