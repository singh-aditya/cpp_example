cmake_minimum_required(VERSION 3.1)

project(grpc_example VERSION 1.0.0)

# Find required protobuf and grpc package
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using Protocol Buffers ${Protobuf_VERSION}")

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# http://www.cmake.org/Wiki/CMake_FAQ#How_can_I_build_my_MSVC_application_with_a_static_runtime.3F
if(MSVC AND Protobuf_MSVC_STATIC_RUNTIME)
  foreach(flag_var
      CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif(${flag_var} MATCHES "/MD")
  endforeach()
endif()

set(protobuf_MODULE_COMPATIBLE ON CACHE BOOL "") # Enable module compatibility to use protobuf-module.cmake

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)

find_program(_PROTOBUF_PROTOC protoc)
if (_PROTOBUF_PROTOC_NOT_FOUND)
  message(FATAL "protoc not found, Check PATH environment var")
endif()

set(_GRPC_GRPCPP gRPC::grpc++)

find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
if (_GRPC_CPP_PLUGIN_EXECUTABLE_NOT_FOUND)
  message(FATAL "grpc_cpp_plugin not found, Check PATH environment var")
endif()


# Proto file
set(proto_file helloworld)
get_filename_component(${PROJECT_NAME}_proto "./proto/${proto_file}.proto" ABSOLUTE)
get_filename_component(${PROJECT_NAME}_proto_path "${${PROJECT_NAME}_proto}" PATH)


# Generated sources
set(${PROJECT_NAME}_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/${proto_file}.pb.cc")
set(${PROJECT_NAME}_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${proto_file}.pb.h")
set(${PROJECT_NAME}_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/${proto_file}.grpc.pb.cc")
set(${PROJECT_NAME}_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${proto_file}.grpc.pb.h")

add_custom_command(
      OUTPUT "${${PROJECT_NAME}_proto_srcs}" "${${PROJECT_NAME}_proto_hdrs}" "${${PROJECT_NAME}_grpc_srcs}" "${${PROJECT_NAME}_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${${PROJECT_NAME}_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${${PROJECT_NAME}_proto}"
      DEPENDS "${${PROJECT_NAME}_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

foreach(_target client server)
  add_executable(${_target} "${_target}/src/${_target}.cpp"
    ${${PROJECT_NAME}_proto_srcs}
    ${${PROJECT_NAME}_grpc_srcs})
  target_link_libraries(${_target}
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})
endforeach()