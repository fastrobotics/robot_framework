add_library(basic_SensorFuserProcess STATIC BasicSensorFuserProcess.cpp)
target_link_libraries(basic_SensorFuserProcess base_SensorFuserProcess)
target_include_directories(basic_SensorFuserProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
