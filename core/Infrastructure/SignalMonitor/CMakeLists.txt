add_library(signalMonitor STATIC SignalMonitor.cpp)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
