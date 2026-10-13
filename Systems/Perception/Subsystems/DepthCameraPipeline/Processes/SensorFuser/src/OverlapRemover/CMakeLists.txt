add_library(overlapRemover STATIC OverlapRemover.cpp)
target_link_libraries(overlapRemover logger infrastructure_msgs sensor_msgs)
target_include_directories(overlapRemover
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_library(DepthCameraPipelineSubsystem::overlapRemover ALIAS overlapRemover)
