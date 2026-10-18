# Test: VisionMsgs::ObjectHypothesisWithPoseMsg
add_executable(test_msgs_VisionMsgs_ObjectHypothesisWithPoseMsg
               test_msgs_VisionMsgs_ObjectHypothesisWithPoseMsg.cpp)
target_link_libraries(test_msgs_VisionMsgs_ObjectHypothesisWithPoseMsg
                      GTest::gtest_main geometry_msgs)

gtest_discover_tests(test_msgs_VisionMsgs_ObjectHypothesisWithPoseMsg)

# Test: VisionMsgs::Detection3DMsg
add_executable(test_msgs_VisionMsgs_Detection3DMsg
               test_msgs_VisionMsgs_Detection3DMsg.cpp)
target_link_libraries(test_msgs_VisionMsgs_Detection3DMsg GTest::gtest_main
                      sensor_msgs geometry_msgs)

gtest_discover_tests(test_msgs_VisionMsgs_Detection3DMsg)
