add_library(basic_FOVExtractorProcess STATIC BasicFOVExtractorProcess.cpp)
target_link_libraries(basic_FOVExtractorProcess base_FOVExtractorProcess)
target_include_directories(basic_FOVExtractorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
