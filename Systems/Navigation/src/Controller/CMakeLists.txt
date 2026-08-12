add_library(base_Controller STATIC BaseController.cpp)
target_link_libraries(base_Controller logger)
target_include_directories(base_Controller
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(PIDController)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
