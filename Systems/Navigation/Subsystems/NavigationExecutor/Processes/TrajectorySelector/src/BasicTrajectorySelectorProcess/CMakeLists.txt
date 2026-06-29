
add_library(basic_TrajectorySelectorProcess STATIC BasicTrajectorySelectorProcess.cpp)
target_link_libraries(basic_TrajectorySelectorProcess base_TrajectorySelectorProcess)
if(BUILD_TESTING)

  add_executable(
    test_basic_TrajectorySelectorProcess
    test/test_BasicTrajectorySelectorProcess.cpp
  )
  target_link_libraries(
    test_basic_TrajectorySelectorProcess
    GTest::gtest_main
    basic_TrajectorySelectorProcess
  )


  gtest_discover_tests(test_basic_TrajectorySelectorProcess)

endif()