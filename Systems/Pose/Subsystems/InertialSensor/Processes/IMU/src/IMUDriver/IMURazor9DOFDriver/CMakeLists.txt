add_library(imuRazor9DOFDriver STATIC IMURazor9DOFDriver.cpp)
target_link_libraries(imuRazor9DOFDriver base_IMUDriver)
target_include_directories(imuRazor9DOFDriver
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
