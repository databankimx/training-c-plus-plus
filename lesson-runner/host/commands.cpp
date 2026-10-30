// commands.cpp: see commands.hpp.

#include "commands.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string_view>

#include <windows.h>
#include <shellapi.h>

namespace fs = std::filesystem;

namespace lesson {
namespace {

std::string lowercase(std::string_view text) {
    std::string result(text);
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return result;
}

bool is_source_file(const fs::path& path) {
    const std::string ext = lowercase(path.extension().string());
    return ext == ".cpp" || ext == ".cc" || ext == ".cxx" || ext == ".h" || ext == ".hpp";
}

// Adds every source file under a folder, as a path relative to root with / separators.
void collect_sources(const fs::path& root, const fs::path& dir, std::vector<std::string>& out) {
    std::error_code ignored;
    if (!fs::is_directory(dir, ignored)) return;
    for (const auto& entry : fs::recursive_directory_iterator(dir, ignored)) {
        if (!entry.is_regular_file(ignored) || !is_source_file(entry.path())) continue;
        std::string relative = fs::relative(entry.path(), root, ignored).generic_string();
        out.push_back(std::move(relative));
    }
}

}  // namespace

std::string read_lesson(const fs::path& step) {
    std::ifstream in(step / "lesson.md", std::ios::binary);
    if (!in) return {};
    std::ostringstream text;
    text << in.rdbuf();
    return text.str();
}

std::string read_step_file(const fs::path& step, const std::string& file) {
    if (file != "lesson.md" && file != "solution.md") return {};
    std::ifstream in(step / file, std::ios::binary);
    if (!in) return {};
    std::ostringstream text;
    text << in.rdbuf();
    return text.str();
}

std::vector<std::string> list_source_files(const fs::path& step) {
    const fs::path src = step / "src";
    const fs::path tests = step / "tests";

    std::vector<std::string> files;
    collect_sources(src, src, files);

    // Test files live in tests, and their names are shown with a tests/ prefix.
    std::vector<std::string> test_files;
    collect_sources(tests, tests, test_files);
    for (auto& file : test_files) files.push_back("tests/" + file);

    // main.cpp comes first, then the rest in alphabetical order.
    std::sort(files.begin(), files.end(), [](const std::string& a, const std::string& b) {
        const bool a_main = a != "main.cpp";
        const bool b_main = b != "main.cpp";
        if (a_main != b_main) return !a_main;
        return a < b;
    });
    return files;
}

std::string read_source(const fs::path& step, const std::string& file) {
    // Refuse anything that could leave the step's folder, and anything that isn't a source file.
    const bool escapes = file.find("..") != std::string::npos || file.starts_with('/') || file.starts_with('\\');
    if (escapes || !is_source_file(file)) {
        throw std::runtime_error("Not a source file: " + file);
    }

    // A name starting with tests/ is in the step's tests folder. Any other name is in src.
    fs::path full = file.starts_with("tests/") ? (step / "tests" / file.substr(6)) : (step / "src" / file);

    std::ifstream in(full, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Could not read " + full.string());
    }
    std::ostringstream text;
    text << in.rdbuf();
    return text.str();
}

std::vector<std::string> read_commands(const fs::path& step) {
    std::ifstream in(step / "commands.txt");
    std::vector<std::string> commands;
    std::string line;
    while (std::getline(in, line)) {
        // Trim spaces, and carriage returns from Windows line endings.
        const auto first = line.find_first_not_of(" \t\r");
        if (first == std::string::npos) continue;
        const auto last = line.find_last_not_of(" \t\r");
        commands.push_back(line.substr(first, last - first + 1));
    }
    return commands;
}

void open_file(const std::string& path, const fs::path& work_folder) {
    const std::string work = work_folder.string();
    if (path.rfind(work, 0) != 0) {
        throw std::runtime_error("Not opening a file outside the run folder: " + path);
    }
    const auto result = reinterpret_cast<INT_PTR>(ShellExecuteA(nullptr, "open", path.c_str(), nullptr, nullptr, SW_SHOWNORMAL));
    if (result <= 32) {
        throw std::runtime_error("Could not open " + path);
    }
}

void open_external(const std::string& url) {
    const bool allowed = url.starts_with("https://") || url.starts_with("http://") || url.starts_with("mailto:");
    if (!allowed) {
        throw std::runtime_error("Not opening " + url);
    }
    const auto result = reinterpret_cast<INT_PTR>(
        ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL));
    // ShellExecute returns a value above 32 on success.
    if (result <= 32) {
        throw std::runtime_error("Could not open " + url);
    }
}

}  // namespace lesson
