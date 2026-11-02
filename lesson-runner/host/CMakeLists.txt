# CMakeLists.txt for the lesson runner's host code.
#
# Builds the shared core (discovery and commands) and the checkpoint tool lesson-list. The window and the process
# runner are added to this file as they're written.
#
# Build with (from the lesson-runner folder):
#   cmake -S host -B build\host -G Ninja
#   cmake --build build\host

cmake_minimum_required(VERSION 3.25)
project(lesson_runner_host LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Writes compile_commands.json, which the editor reads to match the build's settings.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Warnings are on, and kept clean, as the course requires.
add_compile_options(-Wall -Wextra -Wpedantic)

# The vendored nlohmann/json header lives in resources\vendor\nlohmann-json, one level above the host's parent.
set(JSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../resources/vendor/nlohmann-json)

add_library(lesson_core STATIC
    discovery.cpp
    commands.cpp
    router.cpp
    runner.cpp
)
target_include_directories(lesson_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${JSON_INCLUDE_DIR}
)
# ShellExecuteA lives in shell32.
target_link_libraries(lesson_core PUBLIC shell32)

add_executable(lesson-list tools/list_tree.cpp)
target_link_libraries(lesson-list PRIVATE lesson_core)

# The lesson runner window. It's a Windows GUI program, so it uses wWinMain and no console window opens.
# WebView2 headers and the loader come from the SDK that setup.ps1 unpacks into resources\vendor\webview2.
set(WEBVIEW2_SDK ${CMAKE_CURRENT_SOURCE_DIR}/../../resources/vendor/webview2/sdk/build/native)

add_executable(lesson-runner WIN32 app.cpp app.rc)
target_compile_definitions(lesson-runner PRIVATE UNICODE _UNICODE)
target_include_directories(lesson-runner SYSTEM PRIVATE ${WEBVIEW2_SDK}/include)
target_link_options(lesson-runner PRIVATE -municode)
target_link_libraries(lesson-runner PRIVATE lesson_core ole32 uuid)

# The page loads WebView2Loader.dll at run time, so it has to sit next to the program.
add_custom_command(TARGET lesson-runner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${WEBVIEW2_SDK}/x64/WebView2Loader.dll $<TARGET_FILE_DIR:lesson-runner>
    VERBATIM)
