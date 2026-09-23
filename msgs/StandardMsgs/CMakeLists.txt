include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_dependencies(standard_msgs INTERFACE)
target_include_directories(
  standard_msgs INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
add_subdirectory(src)
