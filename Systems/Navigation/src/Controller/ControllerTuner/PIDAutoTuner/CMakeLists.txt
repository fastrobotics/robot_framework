add_library(pid_auto_tuner_Controller STATIC PIDAutoTuner.cpp)
target_link_libraries(pid_auto_tuner_Controller base_Controller pid_Controller
                      logger)
target_include_directories(
  pid_auto_tuner_Controller
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../../../include")

add_library(pid_auto_tuner_Controller_shared STATIC PIDAutoTuner.cpp)

# Forces this duplicate target to compile with -fPIC
set_target_properties(pid_auto_tuner_Controller_shared
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Matches the links and includes of the original
target_link_libraries(pid_auto_tuner_Controller_shared base_Controller
                      pid_Controller logger)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
