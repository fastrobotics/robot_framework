add_library(basic_{{cookiecutter.Process}}Process STATIC
            Basic{{cookiecutter.Process}}Process.cpp)
target_link_libraries(basic_{{cookiecutter.Process}}Process
                      base_{{cookiecutter.Process}}Process)
target_include_directories(basic_{{cookiecutter.Process}}Process
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library({{cookiecutter.Subsystem}}::basic_{{cookiecutter.Process}}Process
            ALIAS basic_{{cookiecutter.Process}}Process)
install(
  TARGETS basic_{{cookiecutter.Process}}Process
  EXPORT {{cookiecutter.Subsystem}}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
