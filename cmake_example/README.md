# cmake_example

This is trivial example with recommended directory structure using CMake to build C++ code.

## Concepts
CMake is cross platform build generate. It is use to generate build files and then make (or any other build automation tool)  can be used to build code. So it is two step process to build code.

CMake reads instruction from text file with name "CMakeLists.txt" (keep same file name). 

It is good practice to define minimum cmake version
`cmake_minimum_required(VERSION 3.0.0)`

Provide Project Name and Version with project command
`project(Project_Name VERSION 1.0.0)`


add_subdirectory can be used to add subdirectory with library files, Each sub_dir would have its own CMakeLists.txt file.
`add_subdirectory(sub_dir)`

add_executable can be used to specify executable and files which are used to build it.
`add_executable(Project_Name
project_files.cpp)`

target_link_libraries is used to link dependecies on target
`target_link_libraries(Project_Name PRIVATE libnames)`

add_library can be used in CMakeLists.txt file to define lib dependent files
`add_library(lib
src/file.cpp)`

target_include_directories can be used in lib CMakeLists.txt file to instruct include directorries. With PUBLIC keyword include directory is visible to parent module and library both.
With INTERFACE keyword include directory is visible to parent module. With PRIVATE keyword include directory is visible to library.
`target_include_directories(libanme PUBLIC include_dir)`

## Build Notes
Generate build file using cmd

`cmake -B build  ` //where "build" is build directory

Build executables using cmd

`cmake --build build --config "release"  ` //where "build" is build directory and config is release 
