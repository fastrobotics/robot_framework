add_library(relay_auto_tune_Controller STATIC RelayAutoTuneController.cpp
                                              MockRelayAutoTuneController.cpp)
target_link_libraries(relay_auto_tune_Controller base_Controller pid_Controller
                      logger)
target_include_directories(
  relay_auto_tune_Controller
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
