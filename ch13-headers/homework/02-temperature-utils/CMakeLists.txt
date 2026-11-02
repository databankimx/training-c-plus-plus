# Temperature utilities: a homework program built from main.cpp and Temperature.cpp.
cmake_minimum_required(VERSION 3.25)
project(temperature_utils LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

if(LESSON_BACKTRACE)
    add_compile_options(-g)
    link_libraries(stdc++exp)
endif()

# Every source file the program uses must be listed here, or the link fails.
add_executable(program src/main.cpp src/Temperature.cpp)
