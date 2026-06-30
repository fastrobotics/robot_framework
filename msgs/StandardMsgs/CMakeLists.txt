include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(standard_msgs INTERFACE)
target_include_directories(standard_msgs
                           INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(src)
