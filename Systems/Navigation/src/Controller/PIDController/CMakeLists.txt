add_library(pid_Controller STATIC PIDController.cpp)
target_link_libraries(pid_Controller base_Controller infrastructure_msgs)
target_include_directories(
  pid_Controller PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../../include")

add_library(pid_Controller_shared SHARED PIDController.cpp)

# Forces this duplicate target to compile with -fPIC
set_target_properties(pid_Controller_shared PROPERTIES POSITION_INDEPENDENT_CODE
                                                       ON)

# Matches the links and includes of the original
target_link_libraries(pid_Controller_shared base_Controller infrastructure_msgs)
target_include_directories(
  pid_Controller_shared PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
