cmake_minimum_required(VERSION 3.0.0)

project(Calculator_Project VERSION 1.0.0)


add_subdirectory(math)

add_subdirectory(print)


add_executable(calculator
main.cpp)


target_link_libraries(calculator PRIVATE mathlib  printlib)




