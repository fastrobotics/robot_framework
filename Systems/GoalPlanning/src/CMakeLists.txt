include(GoogleTest)

add_library(base_GoalPlanning_system STATIC BaseGoalPlanningSystem.cpp)
target_link_libraries(base_GoalPlanning_system geometry_msgs)
add_library(dummy_GoalPlanning_system STATIC DummyGoalPlanningSystem/DummyGoalPlanningSystem.cpp)
target_link_libraries(dummy_GoalPlanning_system base_GoalPlanning_system)

add_executable(
  test_system_GoalPlanning
  test/test_system_GoalPlanning.cpp
)
target_link_libraries(
  test_system_GoalPlanning
  GTest::gtest_main
  geometry_msgs
  GoalPlanning_system_interface
  base_GoalPlanning_system
)


gtest_discover_tests(test_system_GoalPlanning)

add_executable(
  test_DummyGoalPlanningSystem
  test/test_DummyGoalPlanningSystem.cpp
)
target_link_libraries(
  test_DummyGoalPlanningSystem
  GTest::gtest_main
  geometry_msgs
  
  dummy_GoalPlanning_system
)


gtest_discover_tests(test_DummyGoalPlanningSystem)