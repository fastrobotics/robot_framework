add_executable(test_BaseObjectExtractor test_BaseObjectExtractor.cpp)
target_link_libraries(
  test_BaseObjectExtractor GTest::gtest_main
  DepthCameraPipelineSubsystem::baseObjectExtractor infrastructure_msgs logger)
gtest_discover_tests(test_BaseObjectExtractor)

add_executable(test_ObjectExtractorCPU test_ObjectExtractorCPU.cpp)
target_link_libraries(
  test_ObjectExtractorCPU GTest::gtest_main
  DepthCameraPipelineSubsystem::featureExtractorCPU
  DepthCameraPipelineSubsystem::objectExtractorCPU infrastructure_msgs logger)
target_compile_definitions(
  test_ObjectExtractorCPU
  PRIVATE TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")
gtest_discover_tests(test_ObjectExtractorCPU)
