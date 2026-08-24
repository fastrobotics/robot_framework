add_executable(test_subsystem_Interface_NavigationExecutor
               test_subsystem_Interface_NavigationExecutor.cpp)
target_link_libraries(
  test_subsystem_Interface_NavigationExecutor GTest::gtest_main logger
  base_TrajectorySelectorProcess base_TrajectoryControllerProcess
  base_DriveExecutorProcess)

gtest_discover_tests(test_subsystem_Interface_NavigationExecutor)

add_executable(test_subsystem_MinimumFunctionality_NavigationExecutor
               test_subsystem_MinimumFunctionality_NavigationExecutor.cpp)
target_link_libraries(
  test_subsystem_MinimumFunctionality_NavigationExecutor GTest::gtest_main
  logger basic_TrajectorySelectorProcess basic_TrajectoryControllerProcess
  TankDriveExecutorProcess)

gtest_discover_tests(test_subsystem_MinimumFunctionality_NavigationExecutor)
