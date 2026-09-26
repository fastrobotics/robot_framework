add_library(basic_ObjectManagerProcess STATIC BasicObjectManagerProcess.cpp)
target_link_libraries(basic_ObjectManagerProcess base_ObjectManagerProcess)
target_include_directories(basic_ObjectManagerProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
