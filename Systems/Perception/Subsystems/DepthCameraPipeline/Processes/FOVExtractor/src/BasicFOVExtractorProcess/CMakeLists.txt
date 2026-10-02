add_library(basic_FOVExtractorProcess STATIC BasicFOVExtractorProcess.cpp)
target_link_libraries(basic_FOVExtractorProcess base_FOVExtractorProcess)
target_include_directories(basic_FOVExtractorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::basic_FOVExtractorProcess ALIAS
            basic_FOVExtractorProcess)
install(
  TARGETS basic_FOVExtractorProcess
  EXPORT DepthCameraPipelineSubsystem
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
