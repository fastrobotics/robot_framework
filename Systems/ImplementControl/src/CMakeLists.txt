add_library(base_ImplementControl_system STATIC BaseImplementControlSystem.cpp)
target_link_libraries(base_ImplementControl_system geometry_msgs)
add_library(dummy_ImplementControl_system STATIC
            DummyImplementControlSystem/DummyImplementControlSystem.cpp)
target_link_libraries(dummy_ImplementControl_system
                      base_ImplementControl_system)

if(BUILD_TESTING)
  add_executable(test_system_ImplementControl
                 test/test_system_ImplementControl.cpp)
  target_link_libraries(
    test_system_ImplementControl GTest::gtest_main geometry_msgs
    ImplementControl_system_interface base_ImplementControl_system)

  gtest_discover_tests(test_system_ImplementControl)

  add_executable(test_DummyImplementControlSystem
                 test/test_DummyImplementControlSystem.cpp)
  target_link_libraries(test_DummyImplementControlSystem GTest::gtest_main
                        geometry_msgs dummy_ImplementControl_system)

  gtest_discover_tests(test_DummyImplementControlSystem)
endif()
