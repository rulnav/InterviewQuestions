cmake_minimum_required(VERSION 3.10)

project(task1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 99)
# set(CMAKE_C_STANDARD_REQUIRED True)

add_compile_options(-Wall)

add_executable(main main.c)

