add_executable(test_process_GlobalPlannerManager
               test_process_GlobalPlannerManager.cpp)
target_link_libraries(test_process_GlobalPlannerManager GTest::gtest_main
                      base_GlobalPlannerManagerProcess)

gtest_discover_tests(test_process_GlobalPlannerManager)
