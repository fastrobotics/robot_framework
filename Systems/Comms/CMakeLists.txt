include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Comms_system_interface INTERFACE)
target_include_directories(Comms_system_interface INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_subdirectory(src)
add_subdirectory(Subsystems)