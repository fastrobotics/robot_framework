add_library(basic_DepthCameraFeatureHandlerProcess STATIC
            BasicDepthCameraFeatureHandlerProcess.cpp)
target_link_libraries(basic_DepthCameraFeatureHandlerProcess
                      base_DepthCameraFeatureHandlerProcess)
target_include_directories(basic_DepthCameraFeatureHandlerProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
