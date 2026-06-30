add_library(base_{{cookiecutter.System}}_system STATIC
            Base{{cookiecutter.System}}System.cpp)
target_link_libraries(base_{{cookiecutter.System}}_system geometry_msgs)
add_library(
  dummy_{{cookiecutter.System}}_system STATIC
  Dummy{{cookiecutter.System}}System/Dummy{{cookiecutter.System}}System.cpp)
target_link_libraries(dummy_{{cookiecutter.System}}_system
                      base_{{cookiecutter.System}}_system)

if(BUILD_TESTING)

  add_executable(test_system_{{cookiecutter.System}}
                 test/test_system_{{cookiecutter.System}}.cpp)
  target_link_libraries(
    test_system_{{cookiecutter.System}} GTest::gtest_main geometry_msgs
    {{cookiecutter.System}}_system_interface
    base_{{cookiecutter.System}}_system)

  gtest_discover_tests(test_system_{{cookiecutter.System}})

  add_executable(test_Dummy{{cookiecutter.System}}System
                 test/test_Dummy{{cookiecutter.System}}System.cpp)
  target_link_libraries(
    test_Dummy{{cookiecutter.System}}System GTest::gtest_main geometry_msgs
    dummy_{{cookiecutter.System}}_system)

  gtest_discover_tests(test_Dummy{{cookiecutter.System}}System)

endif()
