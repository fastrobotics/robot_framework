add_library(servoHatDriverProcess STATIC ServoHatDriverProcess.cpp)
target_link_libraries(servoHatDriverProcess base_HatDriverProcess)
target_include_directories(servoHatDriverProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
