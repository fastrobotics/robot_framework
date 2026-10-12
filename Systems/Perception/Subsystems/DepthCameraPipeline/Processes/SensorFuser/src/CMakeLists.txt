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

add_library(baseNoiseReducer STATIC BaseNoiseReducer.cpp)
target_link_libraries(baseNoiseReducer PUBLIC sensor_msgs logger
                                              ${PCL_LIBRARIES})
target_include_directories(baseNoiseReducer
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::baseNoiseReducer ALIAS
            baseNoiseReducer)

add_library(noiseReducerCPU STATIC CPUNoiseReducer.cpp)
target_link_libraries(
  noiseReducerCPU
  PUBLIC baseNoiseReducer
  PRIVATE ${PCL_LIBRARIES} OpenMP::OpenMP_CXX)
target_include_directories(noiseReducerCPU
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::noiseReducerCPU ALIAS noiseReducerCPU)

if(ARCHITECTURE_JETSONNANO)
  add_library(noiseReducerGPU STATIC GPUNoiseReducer.cu)
  target_link_libraries(
    noiseReducerGPU
    PUBLIC baseNoiseReducer
    PRIVATE CUDA::cudart)
  target_include_directories(noiseReducerGPU
                             PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
  set_target_properties(noiseReducerGPU PROPERTIES CUDA_STANDARD 17
                                                   CUDA_STANDARD_REQUIRED ON)
  target_compile_options(
    noiseReducerGPU
    PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:--expt-relaxed-constexpr>)
  add_library(DepthCameraPipelineSubsystem::noiseReducerGPU ALIAS
              noiseReducerGPU)
endif()

if(ARCHITECTURE_JETSONNANO)
  set(NOISE_REDUCER_SELECTED_TARGET noiseReducerGPU)
  set(NOISE_REDUCER_INSTALL_TARGETS baseNoiseReducer noiseReducerCPU
                                    noiseReducerGPU)
else()
  set(NOISE_REDUCER_SELECTED_TARGET noiseReducerCPU)
  set(NOISE_REDUCER_INSTALL_TARGETS baseNoiseReducer noiseReducerCPU)
endif()

add_library(base_SensorFuserProcess STATIC BaseSensorFuserProcess.cpp)
target_link_libraries(base_SensorFuserProcess diagnosticManager
                      infrastructure_msgs sensor_msgs combiner)
target_include_directories(base_SensorFuserProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::base_SensorFuserProcess ALIAS
            base_SensorFuserProcess)
install(
  TARGETS combiner overlapRemover ${NOISE_REDUCER_INSTALL_TARGETS}
          base_SensorFuserProcess
  EXPORT DepthCameraPipelineSubsystem
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
add_subdirectory(BasicSensorFuserProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
