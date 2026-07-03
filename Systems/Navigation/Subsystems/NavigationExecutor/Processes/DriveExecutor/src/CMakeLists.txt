add_library(base_DriveExecutorProcess STATIC BaseDriveExecutorProcess.cpp)
target_link_libraries(base_DriveExecutorProcess PUBLIC geometry_msgs infrastructure_msgs)
target_include_directories(base_DriveExecutorProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(BasicDriveExecutorProcess)
add_subdirectory(TankDriveExecutorProcess)

if(BUILD_TESTING)
add_subdirectory(test)
endif()
