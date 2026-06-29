if(BUILD_TESTING)
  add_executable(
    test_StandardMsgs_Vector3DMsg
    test/test_StandardMsgs_Vector3DMsg.cpp
  )
  target_link_libraries(
    test_StandardMsgs_Vector3DMsg
    GTest::gtest_main
  )

  gtest_discover_tests(test_StandardMsgs_Vector3DMsg)

  add_executable(
    test_StandardMsgs_Covariance3DMsg
    test/test_StandardMsgs_Covariance3DMsg.cpp
  )
  target_link_libraries(
    test_StandardMsgs_Covariance3DMsg
    GTest::gtest_main
  )

  gtest_discover_tests(test_StandardMsgs_Covariance3DMsg)

  add_executable(
    test_StandardMsgs_Covariance6DMsg
    test/test_StandardMsgs_Covariance6DMsg.cpp
  )
  target_link_libraries(
    test_StandardMsgs_Covariance6DMsg
    GTest::gtest_main
  )

  gtest_discover_tests(test_StandardMsgs_Covariance6DMsg)
endif()