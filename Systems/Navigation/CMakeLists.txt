include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Navigation_system_interface INTERFACE)
target_include_directories(Navigation_system_interface INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_subdirectory(src)
add_subdirectory(Subsystems)