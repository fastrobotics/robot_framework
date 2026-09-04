# @compare_tag Process-SourceCompile v0.1
add_library(base_HatDriverProcess STATIC BaseHatDriverProcess.cpp)
target_link_libraries(base_HatDriverProcess diagnosticManager
                      infrastructure_msgs)
target_include_directories(base_HatDriverProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(BasicHatDriverProcess)
add_subdirectory(ServoHatDriverProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
