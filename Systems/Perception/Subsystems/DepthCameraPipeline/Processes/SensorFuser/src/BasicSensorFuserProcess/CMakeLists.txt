add_library(basic_SensorFuserProcess STATIC BasicSensorFuserProcess.cpp)
target_link_libraries(
  basic_SensorFuserProcess
  base_SensorFuserProcess
  sensor_msgs
  DepthCameraPipelineSubsystem::combiner
  sensor_msgs
  DepthCameraPipelineSubsystem::overlapRemover
  DepthCameraPipelineSubsystem::noiseReducer)
target_include_directories(basic_SensorFuserProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::basic_SensorFuserProcess ALIAS
            basic_SensorFuserProcess)
install(
  TARGETS basic_SensorFuserProcess
  EXPORT DepthCameraPipelineSubsystem
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
