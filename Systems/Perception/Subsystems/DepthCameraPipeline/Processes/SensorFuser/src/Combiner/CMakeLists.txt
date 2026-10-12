add_library(combiner STATIC Combiner.cpp)
target_link_libraries(combiner logger infrastructure_msgs sensor_msgs)
target_include_directories(combiner
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::combiner ALIAS combiner)
