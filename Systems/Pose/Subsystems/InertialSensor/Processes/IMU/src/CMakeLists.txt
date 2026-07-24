add_subdirectory(IMUDriver)
add_library(base_IMUProcess STATIC BaseIMUProcess.cpp)
target_link_libraries(base_IMUProcess diagnosticManager infrastructure_msgs)
target_include_directories(base_IMUProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

add_library(imuProcess STATIC IMUProcess.cpp)
target_link_libraries(imuProcess base_IMUProcess)
target_include_directories(imuProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
