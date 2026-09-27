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

  # --- FIX: Prevent invalid host flags from bleeding into nvcc ---
  # This tells nvcc exactly how to pass host-specific options down to GCC
  set_target_properties(gpu_math_lib PROPERTIES CUDA_RESOLVE_DEVICE_SYMBOLS ON)

  # If a global tool (like your code coverage tool) is injecting bad flags, you
  # can strip them explicitly for this specific CUDA target:
  get_target_property(CURRENT_COMPILE_OPTIONS gpu_math_lib COMPILE_OPTIONS)
  if(CURRENT_COMPILE_OPTIONS)
    # Clears any global toxic options passed down from parent scope
    set_target_properties(gpu_math_lib PROPERTIES COMPILE_OPTIONS "")
  endif()
endif()

add_executable(math_benchmark main.cpp)
if(ARCHITECTURE_JETSONNANO)
  target_link_libraries(math_benchmark PRIVATE cpu_math_lib gpu_math_lib)
else()
  target_link_libraries(math_benchmark PRIVATE cpu_math_lib)
endif()
install(TARGETS math_benchmark RUNTIME DESTINATION bin)
