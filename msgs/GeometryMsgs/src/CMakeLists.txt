if(BUILD_TESTING)
  add_executable(test_GeometryMsgs_PointMsg test/test_GeometryMsgs_PointMsg.cpp)
  target_link_libraries(test_GeometryMsgs_PointMsg PRIVATE GTest::gtest_main
                                                           geometry_msgs)

  gtest_discover_tests(test_GeometryMsgs_PointMsg)

  add_executable(test_GeometryMsgs_OrientationMsg
                 test/test_GeometryMsgs_OrientationMsg.cpp)
  target_link_libraries(test_GeometryMsgs_OrientationMsg
                        PRIVATE GTest::gtest_main geometry_msgs)

  gtest_discover_tests(test_GeometryMsgs_OrientationMsg)

  add_executable(test_GeometryMsgs_PoseMsg test/test_GeometryMsgs_PoseMsg.cpp)
  target_link_libraries(test_GeometryMsgs_PoseMsg PRIVATE GTest::gtest_main
                                                          geometry_msgs)

  gtest_discover_tests(test_GeometryMsgs_PoseMsg)

  add_executable(test_GeometryMsgs_PoseWithCovarianceMsg
                 test/test_GeometryMsgs_PoseWithCovarianceMsg.cpp)
  target_link_libraries(test_GeometryMsgs_PoseWithCovarianceMsg
                        PRIVATE GTest::gtest_main geometry_msgs)

  gtest_discover_tests(test_GeometryMsgs_PoseWithCovarianceMsg)

  add_executable(test_GeometryMsgs_TwistMsg test/test_GeometryMsgs_TwistMsg.cpp)
  target_link_libraries(test_GeometryMsgs_TwistMsg PRIVATE GTest::gtest_main
                                                           geometry_msgs)

  gtest_discover_tests(test_GeometryMsgs_TwistMsg)

  add_executable(test_GeometryMsgs_TwistWithCovarianceMsg
                 test/test_GeometryMsgs_TwistWithCovarianceMsg.cpp)
  target_link_libraries(test_GeometryMsgs_TwistWithCovarianceMsg
                        PRIVATE GTest::gtest_main geometry_msgs)

  gtest_discover_tests(test_GeometryMsgs_TwistWithCovarianceMsg)

  add_executable(test_GeometryMsgs_OdomMsg test/test_GeometryMsgs_OdomMsg.cpp)
  target_link_libraries(test_GeometryMsgs_OdomMsg PRIVATE GTest::gtest_main
                                                          geometry_msgs)

  gtest_discover_tests(test_GeometryMsgs_OdomMsg)
endif()
