add_library(rerun-protobuf)

target_link_libraries(rerun-protobuf
  protobuf::libprotobuf
)

file(GLOB PROTOS "*.proto")
message("Protos: ${PROTOS}")

PROTOBUF_TARGET_CPP(rerun-protobuf ${CMAKE_CURRENT_SOURCE_DIR} ${PROTOS})
