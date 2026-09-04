# @compare_tag Process-SourceCompile v0.1
add_library(base_TrajectoryControllerProcess STATIC
            BaseTrajectoryControllerProcess.cpp)
target_link_libraries(base_TrajectoryControllerProcess diagnosticManager
                      geometry_msgs sensor_msgs infrastructure_msgs)
target_include_directories(base_TrajectoryControllerProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(BasicTrajectoryControllerProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
