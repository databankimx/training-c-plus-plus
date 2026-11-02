# Options: a program linked against a library whose build is changed by an option.
cmake_minimum_required(VERSION 3.25)
project(options_step LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

# USE_LOUD selects capital letters in the greetings. It is off unless a build turns it on.
option(USE_LOUD "Print greetings in capitals" OFF)

add_library(greeting STATIC src/greeting.cpp)
target_include_directories(greeting PUBLIC src)

if(USE_LOUD)
    target_compile_definitions(greeting PRIVATE LOUD_GREETINGS=1)
endif()

# The runner runs the executable called program, which links the greeting library.
add_executable(program src/main.cpp)
target_link_libraries(program PRIVATE greeting)
