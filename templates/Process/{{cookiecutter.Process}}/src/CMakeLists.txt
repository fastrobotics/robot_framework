add_library(base_{{cookiecutter.Process}}Process STATIC
            Base{{cookiecutter.Process}}Process.cpp)
target_link_libraries(base_{{cookiecutter.Process}}Process diagnosticManager
                      infrastructure_msgs)
add_subdirectory(Basic{{cookiecutter.Process}}Process)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
