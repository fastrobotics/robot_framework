add_library(base_BaseMachine_system STATIC BaseBaseMachineSystem.cpp)
target_link_libraries(base_BaseMachine_system geometry_msgs)
add_library(dummy_BaseMachine_system STATIC
            DummyBaseMachineSystem/DummyBaseMachineSystem.cpp)
target_link_libraries(dummy_BaseMachine_system base_BaseMachine_system)

if(BUILD_TESTING)

  add_executable(test_system_BaseMachine test/test_system_BaseMachine.cpp)
  target_link_libraries(test_system_BaseMachine GTest::gtest_main geometry_msgs
                        BaseMachine_system_interface base_BaseMachine_system)

  gtest_discover_tests(test_system_BaseMachine)

  add_executable(test_DummyBaseMachineSystem
                 test/test_DummyBaseMachineSystem.cpp)
  target_link_libraries(test_DummyBaseMachineSystem GTest::gtest_main
                        geometry_msgs dummy_BaseMachine_system)

  gtest_discover_tests(test_DummyBaseMachineSystem)

endif()
