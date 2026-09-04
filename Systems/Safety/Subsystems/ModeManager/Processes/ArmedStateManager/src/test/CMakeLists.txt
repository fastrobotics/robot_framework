# @compare_tag Process-SourceTestCompile v0.1
add_executable(test_ArmStateCommander test_ArmStateCommander.cpp)
target_link_libraries(test_ArmStateCommander GTest::gtest_main
                      infrastructure_msgs armStateCommander logger)

gtest_discover_tests(test_ArmStateCommander)

add_executable(test_ReadyToArmComputer test_ReadyToArmComputer.cpp)
target_link_libraries(test_ReadyToArmComputer GTest::gtest_main
                      infrastructure_msgs readyToArmComputer)

gtest_discover_tests(test_ReadyToArmComputer)

add_executable(test_process_ArmedStateManager
               test_process_ArmedStateManager.cpp)
target_link_libraries(
  test_process_ArmedStateManager GTest::gtest_main infrastructure_msgs
  base_ArmedStateManagerProcess armedStateManagerProcess)

gtest_discover_tests(test_process_ArmedStateManager)
