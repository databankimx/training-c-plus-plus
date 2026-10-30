# Assertions: a program with a single executable called program.
cmake_minimum_required(VERSION 3.25)
project(assertions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

# The runner builds in Debug mode, so assertions stay active. A release build would define NDEBUG and remove them.
add_executable(program src/main.cpp)
