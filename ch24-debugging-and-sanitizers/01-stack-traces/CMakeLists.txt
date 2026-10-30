# Stack traces: a program that captures its call stack, linked with the stack-trace library.
cmake_minimum_required(VERSION 3.25)
project(stack_traces LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

# With the runner's Backtrace option on, add debug information, so the trace shows function names and lines.
if(LESSON_BACKTRACE)
    add_compile_options(-g)
endif()

# std::stacktrace is in the stdc++exp library on this toolchain, so the program always links it.
add_executable(program src/main.cpp)
target_link_libraries(program PRIVATE stdc++exp)
