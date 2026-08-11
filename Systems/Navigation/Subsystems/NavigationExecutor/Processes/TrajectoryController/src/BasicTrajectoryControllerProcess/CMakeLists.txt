add_library(basic_TrajectoryControllerProcess STATIC
            BasicTrajectoryControllerProcess.cpp)
target_link_libraries(basic_TrajectoryControllerProcess
                      base_TrajectoryControllerProcess pid_Controller)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
