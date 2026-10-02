add_library(basic_FeatureDetectorProcess STATIC BasicFeatureDetectorProcess.cpp)
target_link_libraries(basic_FeatureDetectorProcess
                      DepthCameraPipelineSubsystem::base_FeatureDetectorProcess)
target_include_directories(basic_FeatureDetectorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::basic_FeatureDetectorProcess ALIAS
            basic_FeatureDetectorProcess)
install(
  TARGETS basic_FeatureDetectorProcess
  EXPORT DepthCameraPipelineSubsystem
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
