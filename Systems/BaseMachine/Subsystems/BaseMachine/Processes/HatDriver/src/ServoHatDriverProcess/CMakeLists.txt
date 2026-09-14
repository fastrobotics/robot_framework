if(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "aarch64")
  add_library(servoHatDriver STATIC ServoHatDriver.cpp)
  target_link_libraries(servoHatDriver logger wiringPi)
else()
  add_library(mockServoHatDriver STATIC MockServoHatDriver.cpp)
  target_link_libraries(mockServoHatDriver logger)
endif()

add_library(servoHatDriverProcess STATIC ServoHatDriverProcess.cpp)
if(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "aarch64")
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
