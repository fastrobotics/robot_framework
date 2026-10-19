add_library(baseObjectExtractor STATIC BaseObjectExtractor.cpp)
target_link_libraries(baseObjectExtractor ${PCL_LIBRARIES})
target_include_directories(baseObjectExtractor
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipeline::baseObjectExtractor ALIAS baseObjectExtractor)

add_library(objectExtractorCPU STATIC ObjectExtractorCPU.cpp)
target_link_libraries(objectExtractorCPU baseObjectExtractor)
target_include_directories(objectExtractorCPU
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipeline::objectExtractorCPU ALIAS objectExtractorCPU)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
