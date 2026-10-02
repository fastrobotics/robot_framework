# @compare_tag Process-SourceCompile v0.1
add_library(base_FOVExtractorProcess STATIC BaseFOVExtractorProcess.cpp)
target_link_libraries(base_FOVExtractorProcess diagnosticManager
                      infrastructure_msgs)
target_include_directories(base_FOVExtractorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::base_FOVExtractorProcess ALIAS
            base_FOVExtractorProcess)
install(
  TARGETS base_FOVExtractorProcess
  EXPORT DepthCameraPipelineSubsystem
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
add_subdirectory(BasicFOVExtractorProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
