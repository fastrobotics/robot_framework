include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(sensor_msgs INTERFACE)
target_include_directories(sensor_msgs INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
add_subdirectory(src)