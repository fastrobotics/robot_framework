include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_dependencies(navigation_msgs INTERFACE)
target_include_directories(
  geometry_msgs INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
target_link_libraries(navigation_msgs INTERFACE geometry_msgs)
add_subdirectory(src)
