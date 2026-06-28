add_subdirectory(Basic{{cookiecutter.Process}}Process)
include(GoogleTest)

add_library(base_{{cookiecutter.Process}}Process STATIC Base{{cookiecutter.Process}}Process.cpp)
#target_link_libraries(base_{{cookiecutter.Process}}Process geometry_msgs sensor_msgs)

add_executable(
  test_process_{{cookiecutter.Process}}
  test/test_process_{{cookiecutter.Process}}.cpp
)
target_link_libraries(
  test_process_{{cookiecutter.Process}}
  GTest::gtest_main
  base_{{cookiecutter.Process}}Process
  #geometry_msgs
  #sensor_msgs
)


gtest_discover_tests(test_process_{{cookiecutter.Process}})