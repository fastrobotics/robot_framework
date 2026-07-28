add_executable(test_driver_IMUSYDTM151 test_IMUSYDTM151Driver.cpp)
target_link_libraries(test_driver_IMUSYDTM151 GTest::gtest_main
                      imuSYDTM151Driver infrastructure_msgs)

gtest_discover_tests(test_driver_IMUSYDTM151)
