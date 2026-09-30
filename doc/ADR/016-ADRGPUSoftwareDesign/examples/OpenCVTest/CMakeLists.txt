if(POLICY CMP0146)
  cmake_policy(SET CMP0146 OLD)
endif()
find_package(OpenCV REQUIRED COMPONENTS core imgcodecs imgproc)

add_library(imageProcessTestCPULib STATIC CPUImageProcessor.cpp)
target_include_directories(imageProcessTestCPULib
                           PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(imageProcessTestCPULib PRIVATE ${OpenCV_LIBS})
set(APP_LINK_LIBS imageProcessTestCPULib)
if(ARCHITECTURE_JETSONNANO)
  find_package(OpenCV REQUIRED COMPONENTS cudafilters cudaimgproc)
  add_library(imageProcessTestGPULib STATIC GPUImageProcessor.cpp)
  target_link_libraries(imageProcessTestGPULib PRIVATE ${OpenCV_LIBS})
  target_compile_definitions(imageProcessTestGPULib PRIVATE HAVE_CUDA)

  # Append the GPU library to our executable's link list
  list(APPEND APP_LINK_LIBS imageProcessTestGPULib)
endif()

add_executable(test_opencv main.cpp)
target_link_libraries(test_opencv PRIVATE ${OpenCV_LIBS} ${APP_LINK_LIBS})
target_include_directories(test_opencv PRIVATE ${OpenCV_INCLUDE_DIRS})
install(TARGETS test_opencv RUNTIME DESTINATION bin)
