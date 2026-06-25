include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library({{cookiecutter.package}}_msg INTERFACE)
target_include_directories({{cookiecutter.package}}_msg INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
add_subdirectory(src)