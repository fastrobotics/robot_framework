include(GoogleTest)

add_library(base_Safety_system STATIC BaseSafetySystem.cpp)
target_link_libraries(base_Safety_system geometry_msgs)
add_library(dummy_Safety_system STATIC DummySafetySystem/DummySafetySystem.cpp)
target_link_libraries(dummy_Safety_system base_Safety_system)

add_executable(
  test_system_Safety
  test/test_system_Safety.cpp
)
target_link_libraries(
  test_system_Safety
  GTest::gtest_main
  geometry_msgs
  Safety_system_interface
  base_Safety_system
)


gtest_discover_tests(test_system_Safety)

add_executable(
  test_DummySafetySystem
  test/test_DummySafetySystem.cpp
)
target_link_libraries(
  test_DummySafetySystem
  GTest::gtest_main
  geometry_msgs
  
  dummy_Safety_system
)


gtest_discover_tests(test_DummySafetySystem)