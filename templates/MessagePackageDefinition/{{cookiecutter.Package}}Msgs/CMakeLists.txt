include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_dependencies({{cookiecutter.package}}_msgs INTERFACE)
target_include_directories(
  {{cookiecutter.package}}_msgs
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
target_link_libraries({{cookiecutter.package}}_msgs INTERFACE standard_msgs)
add_subdirectory(src)
