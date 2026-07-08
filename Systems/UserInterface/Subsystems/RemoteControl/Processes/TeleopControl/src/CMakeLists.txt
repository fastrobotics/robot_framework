add_library(base_TeleopControlProcess STATIC BaseTeleopControlProcess.cpp)
target_link_libraries(base_TeleopControlProcess diagnosticManager
                      infrastructure_msgs)
add_subdirectory(BasicTeleopControlProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
