if(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL armv7l)
  add_library(servoHatDriver STATIC ServoHatDriver.cpp)
  target_link_libraries(servoHatDriver logger wiringPi)
else()
  add_library(mockServoHatDriver STATIC MockServoHatDriver.cpp)
  target_link_libraries(mockServoHatDriver logger)
endif()

add_library(servoHatDriverProcess STATIC ServoHatDriverProcess.cpp)
if(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL armv7l)
  target_link_libraries(exec_servohat_driver servoHatDriver logger)
  target_link_libraries(servoHatDriverProcess base_HatDriverProcess
                        servoHatDriver logger)

else()
  target_link_libraries(servoHatDriverProcess base_HatDriverProcess
                        mockServoHatDriver logger)
endif()

target_include_directories(servoHatDriverProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(exec)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
