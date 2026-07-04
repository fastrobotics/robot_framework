add_subdirectory(BasicTrajectorySelectorProcess)

add_library(base_TrajectorySelectorProcess STATIC
            BaseTrajectorySelectorProcess.cpp)
  target_link_libraries(base_TrajectorySelectorProcess diagnosticManager geometry_msgs infrastructure_msgs)


if(BUILD_TESTING)
  add_subdirectory(test)
endif()
