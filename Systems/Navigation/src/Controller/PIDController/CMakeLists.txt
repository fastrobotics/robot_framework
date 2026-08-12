add_library(pid_Controller STATIC PIDController.cpp)
target_link_libraries(pid_Controller base_Controller infrastructure_msgs)
target_include_directories(
  pid_Controller PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
