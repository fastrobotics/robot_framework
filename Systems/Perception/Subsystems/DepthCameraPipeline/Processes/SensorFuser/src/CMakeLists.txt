# @compare_tag Process-SourceCompile v0.1
add_library(combiner STATIC Combiner.cpp)
target_link_libraries(combiner logger infrastructure_msgs sensor_msgs)
target_include_directories(combiner
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::combiner ALIAS combiner)

add_library(overlapRemover STATIC OverlapRemover.cpp)
target_link_libraries(overlapRemover logger infrastructure_msgs sensor_msgs)
target_include_directories(overlapRemover
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::overlapRemover ALIAS overlapRemover)

add_library(noiseReducer STATIC NoiseReducer.cpp)
target_link_libraries(noiseReducer logger infrastructure_msgs sensor_msgs
                      pointCloudTools OpenMP::OpenMP_CXX)
target_include_directories(noiseReducer
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::noiseReducer ALIAS noiseReducer)

add_library(base_SensorFuserProcess STATIC BaseSensorFuserProcess.cpp)
target_link_libraries(base_SensorFuserProcess diagnosticManager
                      infrastructure_msgs sensor_msgs combiner)
target_include_directories(base_SensorFuserProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::base_SensorFuserProcess ALIAS
            base_SensorFuserProcess)
install(
  TARGETS combiner overlapRemover noiseReducer base_SensorFuserProcess
  EXPORT DepthCameraPipelineSubsystem
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
add_subdirectory(BasicSensorFuserProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
