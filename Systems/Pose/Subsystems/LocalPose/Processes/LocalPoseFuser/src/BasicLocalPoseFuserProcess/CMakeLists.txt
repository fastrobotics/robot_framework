add_library(basic_LocalPoseFuserProcess STATIC
            BasicLocalPoseFuserProcess.cpp)
target_link_libraries(basic_LocalPoseFuserProcess
                      base_LocalPoseFuserProcess)
target_include_directories(basic_LocalPoseFuserProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
