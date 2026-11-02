# Include guards: a program built from main.cpp and Battery.cpp, with Battery.h guarded.
cmake_minimum_required(VERSION 3.25)
project(include_guards LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

# With the runner's Backtrace option on, add debug information and the stack-trace library.
if(LESSON_BACKTRACE)
    add_compile_options(-g)
    link_libraries(stdc++exp)
endif()

# The runner runs the executable called program. Every source file of the program is listed here.
add_executable(program src/main.cpp src/Battery.cpp)
