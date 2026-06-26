include(GoogleTest)

add_library(base_Navigation_system STATIC BaseNavigationSystem.cpp)
target_link_libraries(base_Navigation_system geometry_msgs)
add_library(dummy_Navigation_system STATIC DummyNavigationSystem/DummyNavigationSystem.cpp)
target_link_libraries(dummy_Navigation_system base_Navigation_system)

add_executable(
  test_system_Navigation
  test/test_system_Navigation.cpp
)
target_link_libraries(
  test_system_Navigation
  GTest::gtest_main
  geometry_msgs
  Navigation_system_interface
  base_Navigation_system
)


gtest_discover_tests(test_system_Navigation)

add_executable(
  test_DummyNavigationSystem
  test/test_DummyNavigationSystem.cpp
)
target_link_libraries(
  test_DummyNavigationSystem
  GTest::gtest_main
  geometry_msgs
  
  dummy_Navigation_system
)


gtest_discover_tests(test_DummyNavigationSystem)