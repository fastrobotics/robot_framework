add_executable(test_process_GlobalPathStorage
                 test_process_GlobalPathStorage.cpp)
  target_link_libraries(
    test_process_GlobalPathStorage GTest::gtest_main
    base_GlobalPathStorageProcess
    # geometry_msgs sensor_msgs
  )

  gtest_discover_tests(test_process_GlobalPathStorage)