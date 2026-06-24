include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(geometry_msg INTERFACE)
target_include_directories(geometry_msg INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_link_libraries(geometry_msg INTERFACE standard_msg)
add_subdirectory(src)