add_library(base_ArmedStateManagerProcess STATIC
            BaseArmedStateManagerProcess.cpp)
target_link_libraries(base_ArmedStateManagerProcess diagnosticManager
                      infrastructure_msgs)
target_include_directories(base_ArmedStateManagerProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_subdirectory(BasicArmedStateManagerProcess)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
