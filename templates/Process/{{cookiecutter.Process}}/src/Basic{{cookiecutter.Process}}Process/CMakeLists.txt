
add_library(basic_{{cookiecutter.Process}}Process STATIC Basic{{cookiecutter.Process}}Process.cpp)
target_link_libraries(basic_{{cookiecutter.Process}}Process base_{{cookiecutter.Process}}Process)
add_executable(
  test_basic_{{cookiecutter.Process}}Process
  test/test_Basic{{cookiecutter.Process}}Process.cpp
)
target_link_libraries(
  test_basic_{{cookiecutter.Process}}Process
  GTest::gtest_main
  basic_{{cookiecutter.Process}}Process
)


gtest_discover_tests(test_basic_{{cookiecutter.Process}}Process)