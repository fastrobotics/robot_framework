add_executable(test_BaseController test_BaseController.cpp)
target_link_libraries(test_BaseController GTest::gtest_main base_Controller
                      logger)

gtest_discover_tests(test_BaseController)
