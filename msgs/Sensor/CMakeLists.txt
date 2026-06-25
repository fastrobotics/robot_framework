include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(sensor_msg INTERFACE)
target_include_directories(sensor_msg INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
add_subdirectory(src)