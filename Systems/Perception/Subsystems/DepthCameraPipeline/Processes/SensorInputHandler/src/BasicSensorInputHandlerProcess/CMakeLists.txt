add_library(basic_SensorInputHandlerProcess STATIC
            BasicSensorInputHandlerProcess.cpp)
target_link_libraries(basic_SensorInputHandlerProcess
                      base_SensorInputHandlerProcess)
target_include_directories(basic_SensorInputHandlerProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipeline::basic_SensorInputHandlerProcess ALIAS
            basic_SensorInputHandlerProcess)
install(
  TARGETS basic_SensorInputHandlerProcess
  EXPORT DepthCameraPipeline
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
