if(ARCHITECTURE_RASPBERRY_PI)
  find_library(WIRINGPI_LIBRARY NAMES wiringPi REQUIRED)
endif()
if(ARCHITECTURE_RASPBERRY_PI)
  add_library(servoHatDriver STATIC ServoHatDriver.cpp)
  target_link_libraries(servoHatDriver logger ${WIRINGPI_LIBRARY})
else()
  add_library(mockServoHatDriver STATIC MockServoHatDriver.cpp)
  target_link_libraries(mockServoHatDriver logger)
endif()

add_library(servoHatDriverProcess STATIC ServoHatDriverProcess.cpp)
if(ARCHITECTURE_RASPBERRY_PI)
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
