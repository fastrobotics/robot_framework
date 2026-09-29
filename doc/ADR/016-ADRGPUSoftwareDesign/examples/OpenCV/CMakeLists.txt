find_package(OpenCV REQUIRED)
add_executable(test_opencv main.cpp)

# Link the core OpenCV and CUDA modules to the executable
target_link_libraries(test_opencv PRIVATE ${OpenCV_LIBS})
