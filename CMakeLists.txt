cmake_minimum_required(VERSION 3.16...3.27)

project("rerun-ecal-bridge" LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

# Rerun:
include(FetchContent)
FetchContent_Declare(rerun_sdk URL https://github.com/rerun-io/rerun/releases/download/0.15.1/rerun_cpp_sdk.zip)
FetchContent_MakeAvailable(rerun_sdk)

# eCAL
find_package(eCAL REQUIRED)
find_package(Protobuf REQUIRED)

set(protobuf_files
    ${CMAKE_CURRENT_SOURCE_DIR}/protos/Image.proto
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/ReRunLogger.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    src
)

target_link_libraries(${PROJECT_NAME}
    rerun_sdk
    eCAL::core
    eCAL::core_pb
)

PROTOBUF_TARGET_CPP(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/protos/ ${protobuf_files})