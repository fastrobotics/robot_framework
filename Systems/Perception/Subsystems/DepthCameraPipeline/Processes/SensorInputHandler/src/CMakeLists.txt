# @compare_tag Process-SourceCompile v0.1
add_library(base_SensorInputHandlerProcess STATIC
            BaseSensorInputHandlerProcess.cpp)
target_link_libraries(base_SensorInputHandlerProcess diagnosticManager
                      infrastructure_msgs sensor_msgs)
target_include_directories(base_SensorInputHandlerProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipeline::base_SensorInputHandlerProcess ALIAS
            base_SensorInputHandlerProcess)
install(
  TARGETS base_SensorInputHandlerProcess
  EXPORT DepthCameraPipeline
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
add_library(sensorInputHandlerProcess STATIC SensorInputHandlerProcess.cpp)
target_link_libraries(sensorInputHandlerProcess base_SensorInputHandlerProcess)
target_include_directories(sensorInputHandlerProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipeline::sensorInputHandlerProcess ALIAS
            sensorInputHandlerProcess)
install(
  TARGETS sensorInputHandlerProcess
  EXPORT DepthCameraPipeline
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
