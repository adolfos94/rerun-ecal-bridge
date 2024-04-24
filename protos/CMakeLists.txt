add_library(rerun-protobuf)

target_link_libraries(rerun-protobuf
  protobuf::libprotobuf
)

set(PROTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/Image.proto
)

PROTOBUF_TARGET_CPP(rerun-protobuf ${CMAKE_CURRENT_SOURCE_DIR} ${PROTOS})
