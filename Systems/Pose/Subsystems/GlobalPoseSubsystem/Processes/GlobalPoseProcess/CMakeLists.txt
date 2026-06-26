
set(BUILD_DOCUMENTATION OFF CACHE INTERNAL "")
set(BUILD_TOOLS OFF CACHE INTERNAL "")

FetchContent_Declare(
    GeographicLib
    GIT_REPOSITORY https://github.com/geographiclib/geographiclib
    GIT_TAG        v2.5 # Replace with the latest stable version tag
)
FetchContent_MakeAvailable(GeographicLib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)