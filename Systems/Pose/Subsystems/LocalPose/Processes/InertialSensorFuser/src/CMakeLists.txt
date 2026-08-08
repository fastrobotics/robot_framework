add_library(base_InertialSensorFuserProcess STATIC
            BaseInertialSensorFuserProcess.cpp)
target_link_libraries(base_InertialSensorFuserProcess diagnosticManager
                      infrastructure_msgs sensor_msgs geometry_msgs)
target_include_directories(base_InertialSensorFuserProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(BasicInertialSensorFuserProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
