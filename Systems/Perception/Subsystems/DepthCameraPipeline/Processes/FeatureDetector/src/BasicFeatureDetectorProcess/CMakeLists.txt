add_library(basic_FeatureDetectorProcess STATIC BasicFeatureDetectorProcess.cpp)
target_link_libraries(basic_FeatureDetectorProcess base_FeatureDetectorProcess)
target_include_directories(basic_FeatureDetectorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
