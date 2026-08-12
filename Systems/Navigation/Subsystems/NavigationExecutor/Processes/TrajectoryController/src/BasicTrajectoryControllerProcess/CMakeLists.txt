add_library(basic_TrajectoryControllerProcess STATIC
            BasicTrajectoryControllerProcess.cpp)
target_link_libraries(basic_TrajectoryControllerProcess
                      base_TrajectoryControllerProcess pid_Controller)
target_include_directories(basic_TrajectoryControllerProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
