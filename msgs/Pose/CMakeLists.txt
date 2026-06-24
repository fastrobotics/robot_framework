include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(pose_msg INTERFACE)
target_include_directories(pose_msg INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_link_libraries(pose_msg INTERFACE standard_msg)
add_subdirectory(src)