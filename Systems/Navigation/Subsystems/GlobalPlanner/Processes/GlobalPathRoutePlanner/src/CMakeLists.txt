add_subdirectory(BasicGlobalPathRoutePlannerProcess)


add_library(base_GlobalPathRoutePlannerProcess STATIC BaseGlobalPathRoutePlannerProcess.cpp)
#target_link_libraries(base_GlobalPathRoutePlannerProcess geometry_msgs sensor_msgs)

if(BUILD_TESTING)
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
endif()