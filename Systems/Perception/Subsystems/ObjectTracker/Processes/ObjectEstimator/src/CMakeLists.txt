# @compare_tag Process-SourceCompile v0.1
add_library(base_ObjectEstimatorProcess STATIC BaseObjectEstimatorProcess.cpp)
target_link_libraries(base_ObjectEstimatorProcess diagnosticManager
                      infrastructure_msgs)
target_include_directories(base_ObjectEstimatorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(BasicObjectEstimatorProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
