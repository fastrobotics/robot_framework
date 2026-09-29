set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(mathTestCPULib STATIC CPUMath.cpp)
if(ARCHITECTURE_JETSONNANO)
  add_library(mathTestGPULib STATIC GPUMath.cu)
  set_target_properties(mathTestGPULib PROPERTIES LINKER_LANGUAGE CUDA)

endif()

add_executable(test_cpugpu_math_benchmark main.cpp)
if(ARCHITECTURE_JETSONNANO)
  target_link_libraries(test_cpugpu_math_benchmark PRIVATE mathTestCPULib
                                                           mathTestGPULib)
else()
  target_link_libraries(test_cpugpu_math_benchmark PRIVATE mathTestCPULib)
endif()
install(TARGETS test_cpugpu_math_benchmark RUNTIME DESTINATION bin)
