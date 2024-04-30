project(example_points3d LANGUAGES CXX)

add_executable(${PROJECT_NAME} 
  main.cpp
)

target_link_libraries(${PROJECT_NAME}
    rerun_sdk
    eCAL::core
    eCAL::core_pb

    rerun-protobuf
)
