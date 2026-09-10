include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(infrastructure_msgs INTERFACE)
target_include_directories(
  infrastructure_msgs
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
target_link_libraries(infrastructure_msgs INTERFACE robot_framework_definitions)
add_subdirectory(src)
