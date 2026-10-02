# @compare_tag Process-SourceCompile v0.1
add_library(base_{{cookiecutter.Process}}Process STATIC
            Base{{cookiecutter.Process}}Process.cpp)
target_link_libraries(base_{{cookiecutter.Process}}Process diagnosticManager
                      infrastructure_msgs)
target_include_directories(base_{{cookiecutter.Process}}Process
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library({{cookiecutter.Subsystem}}::base_{{cookiecutter.Process}}Process
            ALIAS base_{{cookiecutter.Process}}Process)
install(
  TARGETS base_{{cookiecutter.Process}}Process
  EXPORT {{cookiecutter.Subsystem}}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
add_subdirectory(Basic{{cookiecutter.Process}}Process)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
