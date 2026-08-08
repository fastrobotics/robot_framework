add_library(basic_InertialSensorFuserProcess STATIC
            BasicInertialSensorFuserProcess.cpp)
target_link_libraries(basic_InertialSensorFuserProcess
                      base_InertialSensorFuserProcess)
target_include_directories(basic_InertialSensorFuserProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
