# @compare_tag Process-SourceCompile v0.1
add_library(base_FeatureDetectorProcess STATIC BaseFeatureDetectorProcess.cpp)
target_link_libraries(base_FeatureDetectorProcess diagnosticManager
                      infrastructure_msgs)
target_include_directories(base_FeatureDetectorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::base_FeatureDetectorProcess ALIAS
            base_FeatureDetectorProcess)
install(
  TARGETS base_FeatureDetectorProcess
  EXPORT DepthCameraPipelineSubsystem
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_subdirectory(BasicFeatureDetectorProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
