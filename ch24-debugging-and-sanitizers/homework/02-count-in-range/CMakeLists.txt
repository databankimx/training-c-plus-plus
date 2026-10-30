# Count in range: a homework program with a single executable called program.
cmake_minimum_required(VERSION 3.25)
project(count_in_range LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(program src/main.cpp)
