find_package(PCL 1.14 REQUIRED COMPONENTS common)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_dependencies(sensor_msgs INTERFACE)
target_include_directories(
  sensor_msgs INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
target_include_directories(sensor_msgs INTERFACE ${PCL_INCLUDE_DIRS})
target_link_libraries(sensor_msgs INTERFACE standard_msgs ${PCL_LIBRARIES})
add_subdirectory(src)
