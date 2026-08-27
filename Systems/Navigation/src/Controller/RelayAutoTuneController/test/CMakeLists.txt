add_executable(
  test_RelayAutoTuneController test_RelayAutoTuneController.cpp
                               test_MockRelayAutoTuneController.cpp)
target_link_libraries(test_RelayAutoTuneController GTest::gtest_main
                      relay_auto_tune_Controller logger)
gtest_discover_tests(test_RelayAutoTuneController)
