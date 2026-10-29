# Tests: a program, and a test executable run by CTest.
cmake_minimum_required(VERSION 3.25)
project(tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

# With the runner's Backtrace option on, add debug information and the stack-trace library.
if(LESSON_BACKTRACE)
    add_compile_options(-g)
    link_libraries(stdc++exp)
endif()

# The runner runs the executable called program.
add_executable(program src/main.cpp)
target_include_directories(program PRIVATE src)

# The test executable. The runner's Test button runs it through CTest.
add_executable(tests tests/test_math.cpp)
target_include_directories(tests PRIVATE src)

enable_testing()
add_test(NAME math COMMAND tests)
