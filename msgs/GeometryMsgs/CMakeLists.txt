include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(geometry_msgs INTERFACE)
target_include_directories(geometry_msgs INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_link_libraries(geometry_msgs INTERFACE standard_msgs)
add_subdirectory(src)