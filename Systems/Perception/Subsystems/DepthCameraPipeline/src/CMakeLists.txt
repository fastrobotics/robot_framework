add_library(depthCameraPipelineSubsystem STATIC
            DepthCameraPipelineSubsystem.cpp)
target_link_libraries(
  depthCameraPipelineSubsystem infrastructure_msgs sensor_msgs
  DepthCameraPipelineSubsystem::sensorHealthMonitorProcess
  DepthCameraPipeline::sensorInputHandlerProcess)
target_include_directories(depthCameraPipelineSubsystem
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

install(
  TARGETS depthCameraPipelineSubsystem
  EXPORT DepthCameraPipelineSubsystem
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
