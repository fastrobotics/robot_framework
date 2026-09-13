include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Example_system_interface INTERFACE)
target_include_directories(Example_system_interface
                           INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
add_subdirectory(Subsystems)
