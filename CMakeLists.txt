cmake_minimum_required(VERSION 3.16.3)

project(robot_framework)

if(EXISTS "/etc/nv_tegra_release")
  if(EXISTS "/proc/device-tree/model")
    file(READ "/proc/device-tree/model" DEVICE_MODEL)
    if(DEVICE_MODEL MATCHES "Jetson Nano")
      set(ARCHITECTURE_JETSONNANO TRUE)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DARCHITECTURE_JETSONNANO")
      message(STATUS "ARCHITECTURE: ARCHITECTURE_JETSONNANO")
      add_compile_options(-Wno-psabi)
    endif()
  endif()
elseif(EXISTS "/sys/firmware/devicetree/base/model"
       OR EXISTS "/opt/vc/include/bcm_host.h")
  set(ARCHITECTURE_RASPBERRY_PI TRUE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DARCHITECTURE_RASPBERRY_PI")
  message(STATUS "ARCHITECTURE: ARCHITECTURE_RASPBERRY_PI")
  add_compile_options(-Wno-psabi)
else()
  set(ARCHITECTURE_X8664 TRUE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DARCHITECTURE_X8664")
  message(STATUS "ARCHITECTURE: ARCHITECTURE_X8664")
endif()

add_definitions(-std=c++17 -Wall -Wextra -Wno-switch -Werror)
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
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Infrastruture)
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
add_library(robot_framework_definitions INTERFACE)
target_include_directories(
  robot_framework_definitions
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

macro(add_dependencies TARGET_NAME TARGET_TYPE)
  # 1. Let CMake natively handle creating the library (with or without sources)
  add_library(${TARGET_NAME} ${TARGET_TYPE} ${ARGN})

  # 1. Map the correct linkage type based on the library style
  if("${TARGET_TYPE}" STREQUAL "INTERFACE")
    target_link_libraries(${TARGET_NAME} INTERFACE robot_framework_definitions)
  else()
    target_link_libraries(${TARGET_NAME} PUBLIC robot_framework_definitions)
  endif()
endmacro()
add_subdirectory(msgs)
add_subdirectory(core)
add_subdirectory(Systems)
