include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LINK_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(pcl_example PointCloudExample.cpp)
target_link_libraries(pcl_example ${PCL_LIBRARIES} sensor_msgs)
install(TARGETS pcl_example RUNTIME DESTINATION bin)
