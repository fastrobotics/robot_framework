add_library(basic_HatDriverProcess STATIC BasicHatDriverProcess.cpp)
target_link_libraries(basic_HatDriverProcess base_HatDriverProcess)
target_include_directories(basic_HatDriverProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
if(BUILD_TESTING)

  add_executable(test_basic_HatDriverProcess
                 test/test_BasicHatDriverProcess.cpp)
  target_link_libraries(test_basic_HatDriverProcess GTest::gtest_main
                        basic_HatDriverProcess)

  gtest_discover_tests(test_basic_HatDriverProcess)
endif()
