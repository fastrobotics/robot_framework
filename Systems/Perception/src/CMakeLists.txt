include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LINK_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_library(pointCloudTools STATIC PointCloudTools.cpp)
target_link_libraries(pointCloudTools infrastructure_msgs sensor_msgs
                      ${PCL_LIBRARIES})
target_include_directories(pointCloudTools
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

add_executable(pcl_example PointCloudExample.cpp)
target_link_libraries(pcl_example ${PCL_LIBRARIES} pointCloudTools)
install(TARGETS pcl_example RUNTIME DESTINATION bin)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
