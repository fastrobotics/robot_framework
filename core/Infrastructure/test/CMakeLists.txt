# add_executable(test_Logger test_Logger.cpp) target_link_libraries(test_Logger
# GTest::gtest_main logger) gtest_discover_tests(test_Logger)

add_executable(test_SingletonLogger test_SingletonLogger.cpp)
target_link_libraries(test_SingletonLogger GTest::gtest_main singletonLogger)
gtest_discover_tests(test_SingletonLogger)
