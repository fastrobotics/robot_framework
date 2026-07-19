add_library(armStateCommander STATIC ArmStateCommander.cpp)
target_link_libraries(armStateCommander infrastructure_msgs logger)

add_library(readyToArmComputer STATIC ReadyToArmComputer.cpp)
target_link_libraries(readyToArmComputer infrastructure_msgs logger)

add_library(base_ArmedStateManagerProcess STATIC
            BaseArmedStateManagerProcess.cpp)
target_link_libraries(base_ArmedStateManagerProcess diagnosticManager
                      infrastructure_msgs)
target_include_directories(base_ArmedStateManagerProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(armedStateManagerProcess STATIC ArmedStateManagerProcess.cpp)
target_link_libraries(
  armedStateManagerProcess diagnosticManager infrastructure_msgs
  readyToArmComputer armStateCommander base_ArmedStateManagerProcess)
target_include_directories(armedStateManagerProcess
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
