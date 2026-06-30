add_library(base_Perception_system STATIC BasePerceptionSystem.cpp)
target_link_libraries(base_Perception_system geometry_msgs)
add_library(dummy_Perception_system STATIC
            DummyPerceptionSystem/DummyPerceptionSystem.cpp)
target_link_libraries(dummy_Perception_system base_Perception_system)
if(BUILD_TESTING)

  add_executable(test_system_Perception test/test_system_Perception.cpp)
  target_link_libraries(test_system_Perception GTest::gtest_main geometry_msgs
                        Perception_system_interface base_Perception_system)

  gtest_discover_tests(test_system_Perception)

  add_executable(test_DummyPerceptionSystem test/test_DummyPerceptionSystem.cpp)
  target_link_libraries(test_DummyPerceptionSystem GTest::gtest_main
                        geometry_msgs dummy_Perception_system)

  gtest_discover_tests(test_DummyPerceptionSystem)
endif()
