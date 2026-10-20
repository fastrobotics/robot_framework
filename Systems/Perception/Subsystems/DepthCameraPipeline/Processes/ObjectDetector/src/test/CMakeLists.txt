# @compare_tag Process-SourceTestCompile v0.1

add_executable(test_baseObjectDetector test_BaseObjectDetector.cpp)
target_link_libraries(
  test_baseObjectDetector GTest::gtest_main infrastructure_msgs
  DepthCameraPipeline::base_ObjectDetectorProcess)

gtest_discover_tests(test_baseObjectDetector)

add_executable(test_ObjectDetectorProcess test_ObjectDetectorProcess.cpp)
target_link_libraries(
  test_ObjectDetectorProcess GTest::gtest_main
  DepthCameraPipeline::objectDetectorProcess
  DepthCameraPipelineSubsystem::featureExtractorCPU)
target_compile_definitions(
  test_ObjectDetectorProcess
  PRIVATE TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")
gtest_discover_tests(test_ObjectDetectorProcess)
