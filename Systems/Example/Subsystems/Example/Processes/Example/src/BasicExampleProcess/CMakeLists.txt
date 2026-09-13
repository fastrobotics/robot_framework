add_library(basic_ExampleProcess STATIC BasicExampleProcess.cpp)
target_link_libraries(basic_ExampleProcess base_ExampleProcess)
target_include_directories(basic_ExampleProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
