add_library(base_TeleopControlProcess STATIC BaseTeleopControlProcess.cpp)
target_link_libraries(base_TeleopControlProcess diagnosticManager
                      infrastructure_msgs geometry_msgs)
target_include_directories(base_TeleopControlProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(BasicTeleopControlProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
