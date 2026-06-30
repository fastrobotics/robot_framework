add_library(base_DataStorage_system STATIC BaseDataStorageSystem.cpp)
target_link_libraries(base_DataStorage_system geometry_msgs)
add_library(dummy_DataStorage_system STATIC
            DummyDataStorageSystem/DummyDataStorageSystem.cpp)
target_link_libraries(dummy_DataStorage_system base_DataStorage_system)

if(BUILD_TESTING)
  add_executable(test_system_DataStorage test/test_system_DataStorage.cpp)
  target_link_libraries(test_system_DataStorage GTest::gtest_main geometry_msgs
                        DataStorage_system_interface base_DataStorage_system)

  gtest_discover_tests(test_system_DataStorage)

  add_executable(test_DummyDataStorageSystem
                 test/test_DummyDataStorageSystem.cpp)
  target_link_libraries(test_DummyDataStorageSystem GTest::gtest_main
                        geometry_msgs dummy_DataStorage_system)

  gtest_discover_tests(test_DummyDataStorageSystem)
endif()
