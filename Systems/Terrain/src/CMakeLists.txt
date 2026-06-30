add_library(base_Terrain_system STATIC BaseTerrainSystem.cpp)
target_link_libraries(base_Terrain_system geometry_msgs)
add_library(dummy_Terrain_system STATIC
            DummyTerrainSystem/DummyTerrainSystem.cpp)
target_link_libraries(dummy_Terrain_system base_Terrain_system)

if(BUILD_TESTING)

  add_executable(test_system_Terrain test/test_system_Terrain.cpp)
  target_link_libraries(test_system_Terrain GTest::gtest_main geometry_msgs
                        Terrain_system_interface base_Terrain_system)

  gtest_discover_tests(test_system_Terrain)

  add_executable(test_DummyTerrainSystem test/test_DummyTerrainSystem.cpp)
  target_link_libraries(test_DummyTerrainSystem GTest::gtest_main geometry_msgs
                        dummy_Terrain_system)

  gtest_discover_tests(test_DummyTerrainSystem)
endif()
