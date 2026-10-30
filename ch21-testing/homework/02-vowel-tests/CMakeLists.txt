# Vowel tests: a homework program with a single executable called program, registered as a test.
cmake_minimum_required(VERSION 3.25)
project(vowel_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

if(LESSON_BACKTRACE)
    add_compile_options(-g)
    link_libraries(stdc++exp)
endif()

add_executable(program src/main.cpp)

enable_testing()
add_test(NAME vowel_checks COMMAND program)
