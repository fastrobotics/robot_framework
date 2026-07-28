add_library(
  vendor_lib STATIC
  TransducerM_Lib_Protocol_CPP_V1-2/EasyObjectDictionary.cpp
  TransducerM_Lib_Protocol_CPP_V1-2/EasyProfile.cpp
  TransducerM_Lib_Protocol_CPP_V1-2/EasyProtocol.cpp)
target_include_directories(
  vendor_lib
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/TransducerM_Lib_Protocol_CPP_V1-2)
