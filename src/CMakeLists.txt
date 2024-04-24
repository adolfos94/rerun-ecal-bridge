add_executable(${PROJECT_NAME}
    main.cpp
    ReRunLogger.cpp
 "ISubscriberLogger.hpp")

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
    rerun_sdk
    eCAL::core
    eCAL::core_pb

    rerun-protobuf
)
