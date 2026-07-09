add_library(base_{{cookiecutter.Process}}Process STATIC
            Base{{cookiecutter.Process}}Process.cpp)
target_link_libraries(base_{{cookiecutter.Process}}Process diagnosticManager
                      infrastructure_msgs)
target_include_directories(base_{{cookiecutter.Process}}Process
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(Basic{{cookiecutter.Process}}Process)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
