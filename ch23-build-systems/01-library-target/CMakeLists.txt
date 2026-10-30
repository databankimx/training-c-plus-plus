# Library target: a program linked against a static library target, greeting.
cmake_minimum_required(VERSION 3.25)
project(library_target LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

# The greeting library is built once, from greeting.cpp. Its include folder is shared with anything that links it.
add_library(greeting STATIC src/greeting.cpp)
target_include_directories(greeting PUBLIC src)

# The runner runs the executable called program, which links the greeting library.
add_executable(program src/main.cpp)
target_link_libraries(program PRIVATE greeting)
