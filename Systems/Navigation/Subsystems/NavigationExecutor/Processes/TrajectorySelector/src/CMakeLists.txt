add_subdirectory(BasicTrajectorySelectorProcess)
include(GoogleTest)

add_library(base_TrajectorySelectorProcess STATIC BaseTrajectorySelectorProcess.cpp)
#target_link_libraries(base_TrajectorySelectorProcess geometry_msgs sensor_msgs)

add_executable(
  test_process_TrajectorySelector
  test/test_process_TrajectorySelector.cpp
)
target_link_libraries(
  test_process_TrajectorySelector
  GTest::gtest_main
  base_TrajectorySelectorProcess
  #geometry_msgs
  #sensor_msgs
)


gtest_discover_tests(test_process_TrajectorySelector)