add_executable(exec_imudriver exec_IMUDriver.cpp)
target_link_libraries(exec_imudriver mockIMUDriver imuSYDTM151Driver
                      imuRazor9DOFDriver)
install(TARGETS exec_imudriver RUNTIME DESTINATION bin)
