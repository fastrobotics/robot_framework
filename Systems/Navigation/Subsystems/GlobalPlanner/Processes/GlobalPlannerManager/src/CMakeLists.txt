add_library(base_GlobalPlannerManagerProcess STATIC
            BaseGlobalPlannerManagerProcess.cpp)
target_link_libraries(base_GlobalPlannerManagerProcess diagnosticManager infrastructure_msgs)

add_subdirectory(BasicGlobalPlannerManagerProcess)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
