cmake_minimum_required(VERSION 3.23)

project(robot_framework)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Include the FetchContent module
include(FetchContent)

# Declare GoogleTest dependency
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

#set(BUILD_DOCUMENTATION OFF CACHE INTERNAL "")
#set(BUILD_TOOLS OFF CACHE INTERNAL "")

#FetchContent_Declare(
#    GeographicLib
#    GIT_REPOSITORY https://github.com/geographiclib/geographiclib
#    GIT_TAG        v2.5 # Replace with the latest stable version tag
#)
#FetchContent_MakeAvailable(GeographicLib)

#find_package (GeographicLib REQUIRED)
#include_directories (${GeographicLib_INCLUDE_DIRS}) 


enable_testing()

add_subdirectory(msgs)
add_subdirectory(Systems)