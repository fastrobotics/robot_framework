add_library(basic_FreeSpacePlannerProcess STATIC
            BasicFreeSpacePlannerProcess.cpp)
target_link_libraries(basic_FreeSpacePlannerProcess
                      base_FreeSpacePlannerProcess)

if(BUILD_TESTING)

  add_executable(test_basic_FreeSpacePlannerProcess
                 test/test_BasicFreeSpacePlannerProcess.cpp)
  target_link_libraries(test_basic_FreeSpacePlannerProcess GTest::gtest_main
                        basic_FreeSpacePlannerProcess)

  gtest_discover_tests(test_basic_FreeSpacePlannerProcess)
endif()
