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

set(NOISE_REDUCER_SELECTED_TARGET
    "${NOISE_REDUCER_SELECTED_TARGET}"
    PARENT_SCOPE)
set(NOISE_REDUCER_INSTALL_TARGETS
    "${NOISE_REDUCER_INSTALL_TARGETS}"
    PARENT_SCOPE)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
