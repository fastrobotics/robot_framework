add_library(base_GlobalPathStorageProcess STATIC
            BaseGlobalPathStorageProcess.cpp)
target_link_libraries(base_GlobalPathStorageProcess diagnosticManager infrastructure_msgs)
add_subdirectory(BasicGlobalPathStorageProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
