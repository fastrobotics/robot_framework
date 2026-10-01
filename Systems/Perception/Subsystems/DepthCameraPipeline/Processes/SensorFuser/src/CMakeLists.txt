# @compare_tag Process-SourceCompile v0.1
add_library(base_SensorFuserProcess STATIC BaseSensorFuserProcess.cpp)
target_link_libraries(base_SensorFuserProcess diagnosticManager
                      infrastructure_msgs)
target_include_directories(base_SensorFuserProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(BasicSensorFuserProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
