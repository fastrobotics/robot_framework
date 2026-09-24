add_library(basic_ObjectEstimatorProcess STATIC BasicObjectEstimatorProcess.cpp)
target_link_libraries(basic_ObjectEstimatorProcess base_ObjectEstimatorProcess)
target_include_directories(basic_ObjectEstimatorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
