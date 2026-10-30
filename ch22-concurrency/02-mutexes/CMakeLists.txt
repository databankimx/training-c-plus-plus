# Mutexes: a program with a single executable called program, linked with the thread library.
cmake_minimum_required(VERSION 3.25)
project(mutexes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

# With the runner's Backtrace option on, add debug information and the stack-trace library.
if(LESSON_BACKTRACE)
    add_compile_options(-g)
    link_libraries(stdc++exp)
endif()

# std::thread and std::mutex need the thread library. Threads::Threads adds it to the program.
find_package(Threads REQUIRED)

# The runner runs the executable called program.
add_executable(program src/main.cpp)
target_link_libraries(program PRIVATE Threads::Threads)
