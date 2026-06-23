cmake_minimum_required(VERSION 3.23)

project(learning)
set(CMAKE_INSTALL_PREFIX "install")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Include the FetchContent module
include(FetchContent)

# Declare GoogleTest dependency
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Make GoogleTest available to the build
FetchContent_MakeAvailable(googletest)

# Enable CTest framework support
enable_testing()

add_subdirectory(msgs)
add_subdirectory(Systems)