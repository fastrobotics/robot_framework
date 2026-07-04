add_library(base_FreeSpacePlannerProcess STATIC
              BaseFreeSpacePlannerProcess.cpp)
target_link_libraries(base_FreeSpacePlannerProcess diagnosticManager infrastructure_msgs)
add_subdirectory(BasicFreeSpacePlannerProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
