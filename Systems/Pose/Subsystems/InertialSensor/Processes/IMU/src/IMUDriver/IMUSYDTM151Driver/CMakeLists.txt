add_library(imuSYDTM151Driver STATIC IMUSYDTM151Driver.cpp)
target_link_libraries(imuSYDTM151Driver base_IMUDriver vendor_lib)
target_include_directories(imuSYDTM151Driver
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
