add_subdirectory(BasicTrajectorySelectorProcess)

add_library(base_TrajectorySelectorProcess STATIC
            BaseTrajectorySelectorProcess.cpp)
target_link_libraries(base_TrajectorySelectorProcess diagnosticManager
                      geometry_msgs infrastructure_msgs)
target_include_directories(base_TrajectorySelectorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
