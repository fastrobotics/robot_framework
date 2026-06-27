include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(navigation_msgs INTERFACE)
target_include_directories(navigation_msgs INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_link_libraries(navigation_msgs INTERFACE geometry_msgs)
add_subdirectory(src)