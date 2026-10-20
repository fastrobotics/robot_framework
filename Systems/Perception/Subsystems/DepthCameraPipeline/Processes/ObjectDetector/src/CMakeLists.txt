# @compare_tag Process-SourceCompile v0.1
add_subdirectory(ObjectExtractor)
add_library(base_ObjectDetectorProcess STATIC BaseObjectDetectorProcess.cpp)
target_link_libraries(base_ObjectDetectorProcess diagnosticManager
                      infrastructure_msgs vision_msgs geometry_msgs sensor_msgs)
target_include_directories(base_ObjectDetectorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipeline::base_ObjectDetectorProcess ALIAS
            base_ObjectDetectorProcess)
install(
  TARGETS base_ObjectDetectorProcess
  EXPORT DepthCameraPipeline
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_library(objectDetectorProcess STATIC ObjectDetectorProcess.cpp)
target_link_libraries(
  objectDetectorProcess diagnosticManager infrastructure_msgs
  DepthCameraPipeline::base_ObjectDetectorProcess
  DepthCameraPipelineSubsystem::objectExtractorCPU)
target_include_directories(objectDetectorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipeline::objectDetectorProcess ALIAS
            objectDetectorProcess)
install(
  TARGETS objectDetectorProcess
  EXPORT DepthCameraPipeline
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
