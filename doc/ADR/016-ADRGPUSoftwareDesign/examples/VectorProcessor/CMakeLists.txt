set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Toggle parameter mirroring your custom Jetson configuration
option(ARCHITECTURE_JETSONNANO
       "Build with hardware accelerated GPU offloading enabled" OFF)

# -----------------------------------------------------------------------------
# CPU Target Library
# -----------------------------------------------------------------------------
add_library(cpu_vector_lib STATIC CpuVectorProcessor.cpp)

# Locate and connect the multi-threading dependency to the CPU static library
find_package(OpenMP REQUIRED)
target_link_libraries(cpu_vector_lib PRIVATE OpenMP::OpenMP_CXX)

# -----------------------------------------------------------------------------
# Conditional GPU Target Library
# -----------------------------------------------------------------------------
if(ARCHITECTURE_JETSONNANO)
  add_library(gpu_vector_lib STATIC GpuVectorProcessor.cpp)

  # Instruct nvc++ to convert Standard C++ Parallel loops into GPU code [1.1]
  target_compile_options(gpu_vector_lib PRIVATE -stdpar=gpu)
  target_link_options(gpu_vector_lib PRIVATE -stdpar=gpu)
endif()

# -----------------------------------------------------------------------------
# Benchmark Executable
# -----------------------------------------------------------------------------
add_executable(test_cpugpu_vector_processor main.cpp)

if(ARCHITECTURE_JETSONNANO)
  target_link_libraries(test_cpugpu_vector_processor PRIVATE cpu_vector_lib
                                                             gpu_vector_lib)

  # Inject preprocessor definition so main.cpp safely knows the class exists
  target_compile_definitions(test_cpugpu_vector_processor PRIVATE HAVE_GPU)

  # Ensure final linking phase tracks the NVIDIA offload driver flags
  target_link_options(test_cpugpu_vector_processor PRIVATE -stdpar=gpu)
else()
  target_link_libraries(test_cpugpu_vector_processor PRIVATE cpu_vector_lib)
endif()

# -----------------------------------------------------------------------------
# Installation Rules
# -----------------------------------------------------------------------------
install(TARGETS test_cpugpu_vector_processor RUNTIME DESTINATION bin)
