include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_dependencies(sensor_msgs INTERFACE)
target_include_directories(
  geometry_msgs INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
target_link_libraries(sensor_msgs INTERFACE standard_msgs)
add_subdirectory(src)
