include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library({{cookiecutter.package}}_msgs INTERFACE)
target_include_directories({{cookiecutter.package}}_msgs INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
add_subdirectory(src)