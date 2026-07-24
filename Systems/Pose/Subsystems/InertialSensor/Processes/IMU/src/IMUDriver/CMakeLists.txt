add_library(base_IMUDriver STATIC BaseIMUDriver.cpp)
target_link_libraries(base_IMUDriver sensor_msgs geometry_msgs logger)
target_include_directories(base_IMUDriver
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

add_library(mockIMUDriver STATIC MockIMUDriver.cpp)
target_link_libraries(mockIMUDriver base_IMUDriver)

add_subdirectory(IMUSYDTM151Driver)
add_subdirectory(exec)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
