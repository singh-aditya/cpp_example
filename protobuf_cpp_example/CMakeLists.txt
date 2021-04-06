cmake_minimum_required(VERSION 3.0.0)

project(address_book VERSION 1.0.0)

# Find required protobuf package
find_package(Protobuf REQUIRED)
message(STATUS "Using Protocol Buffers ${Protobuf_VERSION}")

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

foreach(executable_name write read) 
    set(${executable_name}_SRCS ${executable_name}/src/${executable_name}.cpp)
    set(${executable_name}_PROTOS ./proto/addressbook.proto)

    
    #Code Generation
    if(protobuf_MODULE_COMPATIBLE)
    message(STATUS "Using module compatible leagcy support to generate protobuf files for ${executable_name}.")
    set (Protobuf_IMPORT_DIRS ${PROTOBUF_INCLUDE_DIRS}) # add include dir as import dir to find included proto files from google
    protobuf_generate_cpp(${executable_name}_PROTO_SRCS ${executable_name}_PROTO_HDRS
        "${${executable_name}_PROTOS}"
    )
    list(APPEND ${executable_name}_SRCS ${${executable_name}_PROTO_SRCS} ${${executable_name}_PROTO_HDRS})
    endif()

    #Executable setup
    add_executable(${executable_name} ${${executable_name}_SRCS} "${${executable_name}_PROTOS}")
    if(protobuf_MODULE_COMPATIBLE)
    target_include_directories(${executable_name}
        PUBLIC
        ${PROTOBUF_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}
    )
    target_link_libraries(${executable_name}
        ${PROTOBUF_LIBRARIES}
    )
    endif()

endforeach()


