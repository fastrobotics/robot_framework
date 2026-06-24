include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(standard_msg INTERFACE)
target_include_directories(standard_msg INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_subdirectory(src)