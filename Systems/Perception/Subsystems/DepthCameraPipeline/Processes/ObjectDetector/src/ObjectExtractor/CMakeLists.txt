add_library(baseObjectExtractor STATIC BaseObjectExtractor.cpp)
target_link_libraries(
  baseObjectExtractor
  ${PCL_LIBRARIES}
  sensor_msgs
  vision_msgs
  geometry_msgs
  infrastructure_msgs
  logger)
target_include_directories(baseObjectExtractor
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::baseObjectExtractor ALIAS
            baseObjectExtractor)

add_library(objectExtractorCPU STATIC ObjectExtractorCPU.cpp)
target_link_libraries(objectExtractorCPU baseObjectExtractor ${PCL_LIBRARIES})
target_include_directories(objectExtractorCPU
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::objectExtractorCPU ALIAS
            objectExtractorCPU)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
