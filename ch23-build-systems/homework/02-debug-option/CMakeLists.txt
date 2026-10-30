# Debug option: a homework program whose extra output is controlled by an option.
cmake_minimum_required(VERSION 3.25)
project(debug_option LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

# SHOW_STEPS prints each step of the sum. It is off unless the build turns it on.
option(SHOW_STEPS "Print each step of the calculation" OFF)

add_executable(program src/main.cpp)

if(SHOW_STEPS)
    target_compile_definitions(program PRIVATE SHOW_STEPS_ON=1)
endif()
