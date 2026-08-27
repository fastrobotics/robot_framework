add_library(relay_auto_tune_Controller STATIC RelayAutoTuneController.cpp
                                              MockRelayAutoTuneController.cpp)
target_link_libraries(relay_auto_tune_Controller base_Controller pid_Controller
                      logger)
target_include_directories(
  relay_auto_tune_Controller
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../../include")

add_library(relay_auto_tune_Controller_shared STATIC
            RelayAutoTuneController.cpp MockRelayAutoTuneController.cpp)

# Forces this duplicate target to compile with -fPIC
set_target_properties(relay_auto_tune_Controller_shared
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Matches the links and includes of the original
target_link_libraries(relay_auto_tune_Controller_shared base_Controller
                      pid_Controller logger)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
