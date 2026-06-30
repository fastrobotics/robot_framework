cmake_minimum_required(VERSION 3.16.3)

project(robot_framework)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(BUILD_TESTING "Build the test suite" ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
option(ENABLE_COVERAGE "Enable code coverage instrumentation" ON)



if(ENABLE_COVERAGE)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Enabling global code coverage for GCC/Clang")

    # 1. Force debug symbols and turn off optimizations for accurate reports
    add_compile_options(-g -O0)

    # 1. Apply coverage flags to all subsequent source file compilations
    add_compile_options(--coverage)

    # 1. Apply coverage flags to all subsequent binary links
    add_link_options(--coverage)

  elseif(MSVC)
    message(STATUS "Enabling global code coverage for MSVC")
    # MSVC handles coverage through test runner tools (vstest/CodeCoverage.exe)
    # It only requires debug symbols to map binaries back to source files
    add_compile_options(/Zi)
    add_link_options(/DEBUG)
  else()
    message(WARNING "Coverage flags not implemented for this compiler.")
  endif()
endif()

# Include the FetchContent module
include(FetchContent)

if(BUILD_TESTING)
  # Declare GoogleTest dependency
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )

  FetchContent_MakeAvailable(googletest)
  enable_testing()
  include(GoogleTest)
endif()

add_subdirectory(msgs)
add_subdirectory(Systems)
