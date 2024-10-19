cmake_minimum_required(VERSION 3.16...3.27)

project("rerun-ecal-bridge" LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

# Rerun
include(FetchContent)
FetchContent_Declare(rerun_sdk URL
    https://github.com/rerun-io/rerun/releases/latest/download/rerun_cpp_sdk.zip)
FetchContent_MakeAvailable(rerun_sdk)

# eCAL
find_package(eCAL REQUIRED)
find_package(Protobuf REQUIRED)


# Compile protobuf
add_subdirectory(protos)

add_subdirectory(src)
add_subdirectory(samples)