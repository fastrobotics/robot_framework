add_subdirectory(BasicFreeSpacePlannerProcess)
include(GoogleTest)

add_library(base_FreeSpacePlannerProcess STATIC BaseFreeSpacePlannerProcess.cpp)
#target_link_libraries(base_FreeSpacePlannerProcess geometry_msgs sensor_msgs)

add_executable(
  test_process_FreeSpacePlanner
  test/test_process_FreeSpacePlanner.cpp
)
target_link_libraries(
  test_process_FreeSpacePlanner
  GTest::gtest_main
  base_FreeSpacePlannerProcess
  #geometry_msgs
  #sensor_msgs
)


gtest_discover_tests(test_process_FreeSpacePlanner)