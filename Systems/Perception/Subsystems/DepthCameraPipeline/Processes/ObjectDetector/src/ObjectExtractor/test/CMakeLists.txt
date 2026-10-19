add_executable(test_ObjectExtractorCPU test_ObjectExtractorCPU.cpp)
target_link_libraries(
  test_ObjectExtractorCPU GTest::gtest_main
  DepthCameraPipelineSubsystem::featureExtractorCPU
  DepthCameraPipeline::objectExtractorCPU infrastructure_msgs logger)
target_compile_definitions(
  test_ObjectExtractorCPU
  PRIVATE TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")
gtest_discover_tests(test_ObjectExtractorCPU)
