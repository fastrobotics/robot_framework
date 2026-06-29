

add_library(base_UserInterface_system STATIC BaseUserInterfaceSystem.cpp)
target_link_libraries(base_UserInterface_system geometry_msgs)
add_library(dummy_UserInterface_system STATIC DummyUserInterfaceSystem/DummyUserInterfaceSystem.cpp)
target_link_libraries(dummy_UserInterface_system base_UserInterface_system)
if(BUILD_TESTING)


  add_executable(
    test_system_UserInterface
    test/test_system_UserInterface.cpp
  )
  target_link_libraries(
    test_system_UserInterface
    GTest::gtest_main
    geometry_msgs
    UserInterface_system_interface
    base_UserInterface_system
  )


  gtest_discover_tests(test_system_UserInterface)

  add_executable(
    test_DummyUserInterfaceSystem
    test/test_DummyUserInterfaceSystem.cpp
  )
  target_link_libraries(
    test_DummyUserInterfaceSystem
    GTest::gtest_main
    geometry_msgs
    
    dummy_UserInterface_system
  )


  gtest_discover_tests(test_DummyUserInterfaceSystem)
endif()