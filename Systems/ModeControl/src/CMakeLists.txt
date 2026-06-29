add_library(base_ModeControl_system STATIC BaseModeControlSystem.cpp)
target_link_libraries(base_ModeControl_system geometry_msgs)
add_library(dummy_ModeControl_system STATIC DummyModeControlSystem/DummyModeControlSystem.cpp)
target_link_libraries(dummy_ModeControl_system base_ModeControl_system)

if(BUILD_TESTING)
  add_executable(
    test_system_ModeControl
    test/test_system_ModeControl.cpp
  )
  target_link_libraries(
    test_system_ModeControl
    GTest::gtest_main
    geometry_msgs
    ModeControl_system_interface
    base_ModeControl_system
  )


  gtest_discover_tests(test_system_ModeControl)

  add_executable(
    test_DummyModeControlSystem
    test/test_DummyModeControlSystem.cpp
  )
  target_link_libraries(
    test_DummyModeControlSystem
    GTest::gtest_main
    geometry_msgs
    
    dummy_ModeControl_system
  )


  gtest_discover_tests(test_DummyModeControlSystem)
endif()