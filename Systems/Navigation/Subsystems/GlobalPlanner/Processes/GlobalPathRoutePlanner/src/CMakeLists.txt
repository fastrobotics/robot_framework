add_subdirectory(BasicGlobalPathRoutePlannerProcess)
include(GoogleTest)

add_library(base_GlobalPathRoutePlannerProcess STATIC BaseGlobalPathRoutePlannerProcess.cpp)
#target_link_libraries(base_GlobalPathRoutePlannerProcess geometry_msgs sensor_msgs)

add_executable(
  test_process_GlobalPathRoutePlanner
  test/test_process_GlobalPathRoutePlanner.cpp
)
target_link_libraries(
  test_process_GlobalPathRoutePlanner
  GTest::gtest_main
  base_GlobalPathRoutePlannerProcess
  #geometry_msgs
  #sensor_msgs
)


gtest_discover_tests(test_process_GlobalPathRoutePlanner)