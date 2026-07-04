add_library(basic_GlobalPlannerManagerProcess STATIC
            BasicGlobalPlannerManagerProcess.cpp)
target_link_libraries(basic_GlobalPlannerManagerProcess
                      base_GlobalPlannerManagerProcess)

if(BUILD_TESTING)

  add_subdirectory(test)
endif()
