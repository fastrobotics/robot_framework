add_executable(test_driver_IMURazor9DOF test_IMURazor9DOFDriver.cpp)
target_link_libraries(test_driver_IMURazor9DOF GTest::gtest_main
                      imuRazor9DOFDriver infrastructure_msgs)

gtest_discover_tests(test_driver_IMURazor9DOF)
