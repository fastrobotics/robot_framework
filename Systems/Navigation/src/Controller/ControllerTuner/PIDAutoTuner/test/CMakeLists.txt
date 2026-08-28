add_executable(test_PIDAutoTuner test_PIDAutoTuner.cpp)
target_link_libraries(test_PIDAutoTuner GTest::gtest_main
                      pid_auto_tuner_Controller logger)
gtest_discover_tests(test_PIDAutoTuner)
