
add_library(basic_GlobalPathRoutePlannerProcess STATIC BasicGlobalPathRoutePlannerProcess.cpp)
target_link_libraries(basic_GlobalPathRoutePlannerProcess base_GlobalPathRoutePlannerProcess)

if(BUILD_TESTING)

  add_executable(
    test_basic_GlobalPathRoutePlannerProcess
    test/test_BasicGlobalPathRoutePlannerProcess.cpp
  )
  target_link_libraries(
    test_basic_GlobalPathRoutePlannerProcess
    GTest::gtest_main
    basic_GlobalPathRoutePlannerProcess
  )


  gtest_discover_tests(test_basic_GlobalPathRoutePlannerProcess)
endif()