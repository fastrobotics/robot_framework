add_library(joystickMapper STATIC JoystickMapper.cpp)
target_link_libraries(joystickMapper sensor_msgs infrastructure_msgs
                      geometry_msgs)

add_library(joystickScaler STATIC JoystickScaler.cpp)
target_link_libraries(joystickScaler sensor_msgs infrastructure_msgs
                      geometry_msgs logger)

add_library(base_TeleopControlProcess STATIC BaseTeleopControlProcess.cpp)
target_link_libraries(
  base_TeleopControlProcess
  diagnosticManager
  infrastructure_msgs
  geometry_msgs
  sensor_msgs
  joystickMapper
  joystickScaler)
target_include_directories(base_TeleopControlProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

add_subdirectory(BasicTeleopControlProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
