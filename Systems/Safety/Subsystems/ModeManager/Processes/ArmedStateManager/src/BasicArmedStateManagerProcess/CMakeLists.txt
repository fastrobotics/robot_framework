add_library(basic_ArmedStateManagerProcess STATIC
            BasicArmedStateManagerProcess.cpp)
target_link_libraries(basic_ArmedStateManagerProcess
                      base_ArmedStateManagerProcess)
target_include_directories(basic_ArmedStateManagerProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
