# protobuf_cpp_example
This is trivial example on how to use protobuf with C++

## Pre-Requisite
1. Download and Install Cmake from https://cmake.org/download
2. Install vcpkg (cross platform package manager based on c++) from https://github.com/microsoft/vcpkg
   
    It is recommended to clone vcpkg close to root (eg. c:\Git\vcpkg) in order to avoid problems with long files path.
3. Install protobuf using vcpkg
    >vcpkg install protobuf

## Build Notes

Generate build files using cmd
>cmake -B build //where "build" is build directory

Build executables using cmd
>cmake --build build --config "Release" //where "build" is build directory and config is Release mode

Run write exe under build\Release\ as 
>write book //where book is file name to store binary output

Run read exe under build\Release as
>read book //where book is file name to read binary input