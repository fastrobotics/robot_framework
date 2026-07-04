add_library(basic_GlobalPathRoutePlannerProcess STATIC
            BasicGlobalPathRoutePlannerProcess.cpp)
target_link_libraries(basic_GlobalPathRoutePlannerProcess
                      base_GlobalPathRoutePlannerProcess)

if(BUILD_TESTING)

  add_subdirectory(test)
endif()
