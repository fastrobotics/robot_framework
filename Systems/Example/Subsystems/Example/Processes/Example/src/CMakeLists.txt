# @compare_tag Process-SourceCompile v0.1
add_library(base_ExampleProcess STATIC BaseExampleProcess.cpp)
target_link_libraries(base_ExampleProcess diagnosticManager infrastructure_msgs)
target_include_directories(base_ExampleProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(BasicExampleProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
