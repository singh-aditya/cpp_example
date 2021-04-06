## Pre-Requisite:  
Install protobuf and grpc with vcpkg:  
>vcpkg install protobuf  
>vcpkg install grpc

## Commands used to build:

To generate protobuf msgs files:
>protoc -I=. --cpp_out=. helloworld.proto

To generate grpc files:
>protoc -I=. --grpc_out=. --plugin=protoc-gen-grpc="C:\GIT\vcpkg\packages\grpc_x86-windows\tools\grpc\grpc_cpp_plugin.exe" helloworld.proto

Use CMAKE to generate build system files:
>cmake -G "Visual Studio 14 2015" -T host=x86 -A win32  -DCMAKE_TOOLCHAIN_FILE=C:\GIT\vcpkg\scripts\buildsystems\vcpkg.cmake -B build


To generate exe:
>cmake --build build --config release

