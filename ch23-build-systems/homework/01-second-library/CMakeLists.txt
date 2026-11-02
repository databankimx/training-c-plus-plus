# Second library: a program linked against a second static library target, mathutil.
cmake_minimum_required(VERSION 3.25)
project(second_library LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

add_library(mathutil STATIC src/mathutil.cpp)
target_include_directories(mathutil PUBLIC src)

add_executable(program src/main.cpp)
target_link_libraries(program PRIVATE mathutil)
