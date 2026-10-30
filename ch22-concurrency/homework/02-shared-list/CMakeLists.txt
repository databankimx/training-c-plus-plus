# Shared list: a homework program with a single executable called program, linked with the thread library.
cmake_minimum_required(VERSION 3.25)
project(shared_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

if(LESSON_BACKTRACE)
    add_compile_options(-g)
    link_libraries(stdc++exp)
endif()

find_package(Threads REQUIRED)

add_executable(program src/main.cpp)
target_link_libraries(program PRIVATE Threads::Threads)
