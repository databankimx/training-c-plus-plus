# Finding bugs: a program with a single executable called program, built for debugging.
cmake_minimum_required(VERSION 3.25)
project(finding_bugs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

# The debugger needs debug information, which the -g flag adds.
add_compile_options(-g)

add_executable(program src/main.cpp)
