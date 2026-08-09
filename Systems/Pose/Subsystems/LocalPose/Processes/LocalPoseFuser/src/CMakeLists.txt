add_library(base_LocalPoseFuserProcess STATIC BaseLocalPoseFuserProcess.cpp)
target_link_libraries(base_LocalPoseFuserProcess diagnosticManager
                      infrastructure_msgs sensor_msgs geometry_msgs)
target_include_directories(base_LocalPoseFuserProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(BasicLocalPoseFuserProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
