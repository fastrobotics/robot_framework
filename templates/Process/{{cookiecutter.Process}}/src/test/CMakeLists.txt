add_executable(test_process_{{cookiecutter.Process}}
               test_process_{{cookiecutter.Process}}.cpp)
target_link_libraries(test_process_{{cookiecutter.Process}} GTest::gtest_main
                      infrastructure_msgs base_{{cookiecutter.Process}}Process)

gtest_discover_tests(test_process_{{cookiecutter.Process}})
