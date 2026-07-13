add_library(basic_{{cookiecutter.Process}}Process STATIC
            Basic{{cookiecutter.Process}}Process.cpp)
target_link_libraries(basic_{{cookiecutter.Process}}Process
                      base_{{cookiecutter.Process}}Process)
target_include_directories(basic_{{cookiecutter.Process}}Process
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
