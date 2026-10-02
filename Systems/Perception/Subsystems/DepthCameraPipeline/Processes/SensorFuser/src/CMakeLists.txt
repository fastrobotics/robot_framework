# @compare_tag Process-SourceCompile v0.1
add_library(base_SensorFuserProcess STATIC BaseSensorFuserProcess.cpp)
target_link_libraries(base_SensorFuserProcess diagnosticManager
                      infrastructure_msgs)
target_include_directories(base_SensorFuserProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::base_SensorFuserProcess ALIAS
            base_SensorFuserProcess)
install(
  TARGETS base_SensorFuserProcess
  EXPORT DepthCameraPipelineSubsystem
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
add_subdirectory(BasicSensorFuserProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
