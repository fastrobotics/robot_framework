add_subdirectory(BasicGlobalPlannerManagerProcess)
include(GoogleTest)

add_library(base_GlobalPlannerManagerProcess STATIC BaseGlobalPlannerManagerProcess.cpp)
#target_link_libraries(base_GlobalPlannerManagerProcess geometry_msgs sensor_msgs)

add_executable(
  test_process_GlobalPlannerManager
  test/test_process_GlobalPlannerManager.cpp
)
target_link_libraries(
  test_process_GlobalPlannerManager
  GTest::gtest_main
  base_GlobalPlannerManagerProcess
  #geometry_msgs
  #sensor_msgs
)


gtest_discover_tests(test_process_GlobalPlannerManager)