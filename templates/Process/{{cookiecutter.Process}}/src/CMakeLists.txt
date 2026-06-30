add_subdirectory(Basic{{cookiecutter.Process}}Process)

add_library(base_{{cookiecutter.Process}}Process STATIC
            Base{{cookiecutter.Process}}Process.cpp)
if(BUILD_TESTING)

  # target_link_libraries(base_{{cookiecutter.Process}}Process geometry_msgs
  # sensor_msgs)

  add_executable(test_process_{{cookiecutter.Process}}
                 test/test_process_{{cookiecutter.Process}}.cpp)
  target_link_libraries(
    test_process_{{cookiecutter.Process}} GTest::gtest_main
    base_{{cookiecutter.Process}}Process
    # geometry_msgs sensor_msgs
  )

  gtest_discover_tests(test_process_{{cookiecutter.Process}})
endif()
