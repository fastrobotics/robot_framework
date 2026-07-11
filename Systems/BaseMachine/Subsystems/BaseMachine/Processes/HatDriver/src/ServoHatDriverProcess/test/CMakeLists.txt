add_executable(test_ServoHatDriverProcess test_ServoHatDriverProcess.cpp)
target_link_libraries(test_ServoHatDriverProcess GTest::gtest_main
                      ServoHatDriverProcess)

gtest_discover_tests(test_ServoHatDriverProcess)
