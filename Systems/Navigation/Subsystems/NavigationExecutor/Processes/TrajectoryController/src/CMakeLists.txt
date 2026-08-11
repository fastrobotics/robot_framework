add_library(base_TrajectoryControllerProcess STATIC
            BaseTrajectoryControllerProcess.cpp)
target_link_libraries(base_TrajectoryControllerProcess diagnosticManager
                      geometry_msgs sensor_msgs infrastructure_msgs)
add_subdirectory(BasicTrajectoryControllerProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
