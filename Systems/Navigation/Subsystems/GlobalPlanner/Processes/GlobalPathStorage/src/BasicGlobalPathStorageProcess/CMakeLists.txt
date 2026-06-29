
add_library(basic_GlobalPathStorageProcess STATIC BasicGlobalPathStorageProcess.cpp)
target_link_libraries(basic_GlobalPathStorageProcess base_GlobalPathStorageProcess)

if(BUILD_TESTING)

  add_executable(
    test_basic_GlobalPathStorageProcess
    test/test_BasicGlobalPathStorageProcess.cpp
  )
  target_link_libraries(
    test_basic_GlobalPathStorageProcess
    GTest::gtest_main
    basic_GlobalPathStorageProcess
  )


  gtest_discover_tests(test_basic_GlobalPathStorageProcess)
endif()