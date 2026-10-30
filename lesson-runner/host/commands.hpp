// commands.hpp: the read-only commands the front end calls. They take plain values and return plain values, so
// they can be tested without a window. The host's message router turns them into JSON replies.

#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace lesson {

// The text of a step's lesson.md, or an empty string if it has none.
std::string read_lesson(const std::filesystem::path& step);

// A text file from a step folder that the lesson pane may show. Only lesson.md and solution.md are allowed,
// so any other name gives an empty string.
std::string read_step_file(const std::filesystem::path& step, const std::string& file);

// The C++ source files in a step's src folder, and its tests folder. Names are relative to src, with
// tests/ in front of the test files. main.cpp comes first.
std::vector<std::string> list_source_files(const std::filesystem::path& step);

// The text of one source file, named as list_source_files names it. Throws std::runtime_error with the
// message the front end shows if the name is not allowed or the file can't be read.
std::string read_source(const std::filesystem::path& step, const std::string& file);

// Quick picks: one command per non-empty line in the step's commands.txt.
std::vector<std::string> read_commands(const std::filesystem::path& step);

// Opens a web or mail link in the default browser. Anything else is refused. Throws on refusal or failure.
void open_external(const std::string& url);

// Opens a file from a run's work folder in the default application for its type. Files outside that folder are
// refused. Throws on refusal or failure.
void open_file(const std::string& path, const std::filesystem::path& work_folder);

}  // namespace lesson
