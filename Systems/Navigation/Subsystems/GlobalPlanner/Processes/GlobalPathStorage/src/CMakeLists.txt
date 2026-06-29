add_subdirectory(BasicGlobalPathStorageProcess)

add_library(base_GlobalPathStorageProcess STATIC BaseGlobalPathStorageProcess.cpp)
#target_link_libraries(base_GlobalPathStorageProcess geometry_msgs sensor_msgs)

if(BUILD_TESTING)

  add_executable(
    test_process_GlobalPathStorage
    test/test_process_GlobalPathStorage.cpp
  )
  target_link_libraries(
    test_process_GlobalPathStorage
    GTest::gtest_main
    base_GlobalPathStorageProcess
    #geometry_msgs
    #sensor_msgs
  )


  gtest_discover_tests(test_process_GlobalPathStorage)
endif()