# Core calculator: a program with a single executable called program, and its checks registered with CTest.
cmake_minimum_required(VERSION 3.25)
project(calculator_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

if(LESSON_BACKTRACE)
    add_compile_options(-g)
    link_libraries(stdc++exp)
endif()

add_executable(program src/main.cpp)

# The Test button runs CTest, which runs the program's selftest mode and reads its exit code.
enable_testing()
add_test(NAME calculator_checks COMMAND program selftest)
