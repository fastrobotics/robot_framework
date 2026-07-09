add_library(remoteControlTwistComputer STATIC TwistComputer.cpp)
target_link_libraries(remoteControlTwistComputer geometry_msgs sensor_msgs)

add_library(basic_TeleopControlProcess STATIC BasicTeleopControlProcess.cpp)
target_link_libraries(basic_TeleopControlProcess base_TeleopControlProcess
                      remoteControlTwistComputer)
target_include_directories(basic_TeleopControlProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
