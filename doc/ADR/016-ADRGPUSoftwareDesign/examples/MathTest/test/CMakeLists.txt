add_executable(test_CPUMath test_CPUMath.cpp)
target_link_libraries(test_CPUMath PRIVATE mathTestCPULib GTest::gtest_main)
gtest_discover_tests(test_CPUMath)
