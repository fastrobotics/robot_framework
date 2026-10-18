include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_dependencies(vision_msgs INTERFACE)
target_include_directories(
  vision_msgs INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
target_link_libraries(vision_msgs INTERFACE standard_msgs)
add_subdirectory(src)
