include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library({{cookiecutter.Message}}_msg INTERFACE)
target_include_directories({{cookiecutter.Message}}_msg INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
add_subdirectory(src)