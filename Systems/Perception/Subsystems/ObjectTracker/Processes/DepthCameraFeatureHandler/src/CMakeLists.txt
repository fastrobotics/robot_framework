# @compare_tag Process-SourceCompile v0.1
add_library(base_DepthCameraFeatureHandlerProcess STATIC
            BaseDepthCameraFeatureHandlerProcess.cpp)
target_link_libraries(base_DepthCameraFeatureHandlerProcess diagnosticManager
                      infrastructure_msgs)
target_include_directories(base_DepthCameraFeatureHandlerProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(BasicDepthCameraFeatureHandlerProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
