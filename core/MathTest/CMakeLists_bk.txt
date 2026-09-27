set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(cpu_math_lib STATIC cpu_math.cpp)
if(ARCHITECTURE_JETSONNANO)
  set(CMAKE_CUDA_ARCHITECTURES 87)
  set(CMAKE_CUDA_STANDARD 17)
  set(CMAKE_CUDA_STANDARD_REQUIRED ON)

  if(NOT CMAKE_CUDA_COMPILER)
    set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc)
  endif()

  enable_language(CUDA)
  find_package(CUDAToolkit REQUIRED)

  add_library(gpu_math_lib STATIC gpu_math.cu)
  target_link_libraries(gpu_math_lib PRIVATE CUDA::cudart)
  set_target_properties(gpu_math_lib PROPERTIES LINKER_LANGUAGE CUDA)

  # --- THE FIX: Wipe out parent options and conditionally add flags ---
  set_target_properties(gpu_math_lib PROPERTIES COMPILE_OPTIONS "")

  # If you need standard compile settings later, safely apply them using
  # language guards:
  target_compile_options(
    gpu_math_lib
    PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-Werror> # Only passed to CPU files if any
                                               # are added here
  )

endif()

add_executable(math_benchmark main.cpp)
if(ARCHITECTURE_JETSONNANO)
  target_link_libraries(math_benchmark PRIVATE cpu_math_lib gpu_math_lib)
else()
  target_link_libraries(math_benchmark PRIVATE cpu_math_lib)
endif()
install(TARGETS math_benchmark RUNTIME DESTINATION bin)
