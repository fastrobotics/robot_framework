add_library(base_FeatureExtractor STATIC BaseFeatureExtractor.cpp)
target_link_libraries(base_FeatureExtractor infrastructure_msgs sensor_msgs
                      logger)
target_include_directories(base_FeatureExtractor
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::base_FeatureExtractor ALIAS
            base_FeatureExtractor)

add_library(featureExtractorCPU STATIC FeatureExtractorCPU.cpp)
target_link_libraries(featureExtractorCPU base_FeatureExtractor
                      ${PCL_LIBRARIES})
target_include_directories(featureExtractorCPU
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::featureExtractorCPU ALIAS
            featureExtractorCPU)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
