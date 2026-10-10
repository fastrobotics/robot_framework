find_package(PCL 1.14 REQUIRED COMPONENTS common filters io visualization)
include_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Perception_system_interface INTERFACE)
target_include_directories(Perception_system_interface
                           INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
add_subdirectory(src)
add_subdirectory(Subsystems)
