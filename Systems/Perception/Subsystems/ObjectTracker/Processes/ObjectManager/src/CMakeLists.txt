# @compare_tag Process-SourceCompile v0.1
add_library(base_ObjectManagerProcess STATIC BaseObjectManagerProcess.cpp)
target_link_libraries(base_ObjectManagerProcess diagnosticManager
                      infrastructure_msgs)
target_include_directories(base_ObjectManagerProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(BasicObjectManagerProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
