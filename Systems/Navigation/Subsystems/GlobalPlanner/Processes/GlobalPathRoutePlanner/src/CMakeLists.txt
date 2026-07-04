add_library(base_GlobalPathRoutePlannerProcess STATIC
            BaseGlobalPathRoutePlannerProcess.cpp)
target_link_libraries(base_GlobalPathRoutePlannerProcess diagnosticManager infrastructure_msgs)

add_subdirectory(BasicGlobalPathRoutePlannerProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
