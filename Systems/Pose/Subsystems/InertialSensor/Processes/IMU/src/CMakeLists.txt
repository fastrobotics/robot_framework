# @compare_tag Process-SourceCompile v0.1
add_subdirectory(IMUDriver)
add_library(base_IMUProcess STATIC BaseIMUProcess.cpp)
target_link_libraries(
  base_IMUProcess
  diagnosticManager
  infrastructure_msgs
  sensor_msgs
  geometry_msgs
  mockIMUDriver
  imuSYDTM151Driver
  imuRazor9DOFDriver)
target_include_directories(base_IMUProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

add_library(imuProcess STATIC IMUProcess.cpp)
target_link_libraries(imuProcess base_IMUProcess)
target_include_directories(imuProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../include/" # Direct pointer to your
                                                      # sibling include folder
  DESTINATION include # Centralized workspace built include folder
)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
