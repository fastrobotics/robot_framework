add_executable(test_basic_GlobalPlannerManagerProcess
               test_BasicGlobalPlannerManagerProcess.cpp)
target_link_libraries(test_basic_GlobalPlannerManagerProcess GTest::gtest_main
                      basic_GlobalPlannerManagerProcess)

gtest_discover_tests(test_basic_GlobalPlannerManagerProcess)
