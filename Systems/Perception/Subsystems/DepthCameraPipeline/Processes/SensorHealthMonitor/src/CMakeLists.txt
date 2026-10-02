# @compare_tag Process-SourceCompile v0.1
add_library(base_SensorHealthMonitorProcess STATIC
            BaseSensorHealthMonitorProcess.cpp)
target_link_libraries(base_SensorHealthMonitorProcess diagnosticManager
                      infrastructure_msgs)
target_include_directories(base_SensorHealthMonitorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::base_SensorHealthMonitorProcess ALIAS
            base_SensorHealthMonitorProcess)
install(
  TARGETS base_SensorHealthMonitorProcess
  EXPORT DepthCameraPipelineSubsystem
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_library(sensorHealthMonitorProcess STATIC SensorHealthMonitorProcess.cpp)
target_link_libraries(sensorHealthMonitorProcess
                      base_SensorHealthMonitorProcess)
target_include_directories(sensorHealthMonitorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::sensorHealthMonitorProcess ALIAS
            sensorHealthMonitorProcess)
install(
  TARGETS sensorHealthMonitorProcess
  EXPORT DepthCameraPipelineSubsystem
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
