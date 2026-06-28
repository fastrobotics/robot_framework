
add_library(TankDriveExecutorProcess STATIC TankDriveExecutorProcess.cpp)
target_link_libraries(TankDriveExecutorProcess base_DriveExecutorProcess)
add_executable(
  test_TankDriveExecutorProcess
  test/test_TankDriveExecutorProcess.cpp
)
target_link_libraries(
  test_TankDriveExecutorProcess
  GTest::gtest_main
  TankDriveExecutorProcess
  geometry_msgs
)


gtest_discover_tests(test_TankDriveExecutorProcess)