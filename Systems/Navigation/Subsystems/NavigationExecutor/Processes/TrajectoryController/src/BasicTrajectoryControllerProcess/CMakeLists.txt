add_library(basic_TrajectoryControllerProcess STATIC
            BasicTrajectoryControllerProcess.cpp)
target_link_libraries(basic_TrajectoryControllerProcess
                      base_TrajectoryControllerProcess)
if(BUILD_TESTING)
  add_subdirecctory(test)
endif()
