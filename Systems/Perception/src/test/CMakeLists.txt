add_executable(test_pointCloudTools test_pointCloudTools.cpp)
target_link_libraries(test_pointCloudTools GTest::gtest_main
                      infrastructure_msgs pointCloudTools)
target_compile_options(test_pointCloudTools PRIVATE -O3 -march=native)
gtest_discover_tests(test_pointCloudTools)
