
add_library(base_Comms_system STATIC BaseCommsSystem.cpp)
target_link_libraries(base_Comms_system geometry_msgs)
add_library(dummy_Comms_system STATIC DummyCommsSystem/DummyCommsSystem.cpp)
target_link_libraries(dummy_Comms_system base_Comms_system)

if(BUILD_TESTING)

  add_executable(test_system_Comms test/test_system_Comms.cpp)
  target_link_libraries(test_system_Comms GTest::gtest_main geometry_msgs
                        Comms_system_interface base_Comms_system)

  gtest_discover_tests(test_system_Comms)

  add_executable(test_DummyCommsSystem test/test_DummyCommsSystem.cpp)
  target_link_libraries(test_DummyCommsSystem GTest::gtest_main geometry_msgs
                        dummy_Comms_system)

  gtest_discover_tests(test_DummyCommsSystem)
endif()
