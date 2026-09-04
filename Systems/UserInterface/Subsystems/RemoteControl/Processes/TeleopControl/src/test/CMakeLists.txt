# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_joysticMapper test_JoystickMapper.cpp)
target_link_libraries(test_joysticMapper GTest::gtest_main joystickMapper)
gtest_discover_tests(test_joysticMapper)

add_executable(test_joysticScaler test_JoystickScaler.cpp)
target_link_libraries(test_joysticScaler GTest::gtest_main joystickScaler)
gtest_discover_tests(test_joysticScaler)

add_executable(test_process_TeleopControl test_process_TeleopControl.cpp)
target_link_libraries(test_process_TeleopControl GTest::gtest_main
                      base_TeleopControlProcess)
gtest_discover_tests(test_process_TeleopControl)
