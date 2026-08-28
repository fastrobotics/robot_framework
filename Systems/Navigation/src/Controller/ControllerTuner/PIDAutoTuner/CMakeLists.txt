add_library(pid_auto_tuner_Controller STATIC PIDAutoTuner.cpp)
target_link_libraries(pid_auto_tuner_Controller base_Controller pid_Controller
                      logger)
target_include_directories(
  pid_auto_tuner_Controller
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../../../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
