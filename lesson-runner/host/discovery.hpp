// discovery.hpp: finds the chapters, sections, steps, and homework in the training repository.
// The rules match the Rust runner's discovery.rs, with two differences for C++: a step has a CMakeLists.txt rather
// than a Cargo.toml, and tests are found by TEST_CASE rather than #[test].

#pragma once

#include <json.hpp>

#include <filesystem>
#include <string>
#include <vector>

namespace lesson {

// The options a step declares with option(NAME "description" ON|OFF) in its CMakeLists.txt.
struct StepOption {
    std::string name;
    std::string description;
    bool default_on = false;
};

struct Step {
    std::string name;
    std::string title;
    std::string path;
    bool has_code = false;
    bool has_tests = false;
    bool has_main = false;
    bool has_visualizer = false;
    std::vector<StepOption> options;  // The option(...) lines in the step's CMakeLists.txt, for the page's checkboxes.
};

struct Section {
    std::string name;
    std::string title;
    std::string path;
    std::vector<Step> steps;
};

struct Chapter {
    std::string name;
    std::string title;
    std::string path;
    std::vector<Step> steps;
    std::vector<Step> homework;
    std::string homework_path;
    std::string homework_title;  // The label above the homework list. It's "Homework" unless the folder says otherwise.
    std::vector<Section> sections;
};

// Walks up from a starting folder (normally the program's own folder) until it finds the folder that holds
// lesson-runner. That folder is the training repository's root.
std::filesystem::path find_repo_root(const std::filesystem::path& start);

// Every chapter folder in the repository, in chapter order.
std::vector<Chapter> discover(const std::filesystem::path& root);

// The chapters grouped by the parts named in parts.json at the repository root. Chapters that no part names
// are grouped under "Other", and parts with no chapters are left out.
nlohmann::json list_parts(const std::filesystem::path& root);

// The folder where runs are built and run: a fixed place inside the repository, so one folder exclusion in a
// security product covers every run. It is ignored by git.
std::filesystem::path work_root(const std::filesystem::path& repo_root);

// Reads the option(...) lines of a step's CMakeLists.txt. Commented lines are skipped.
std::vector<StepOption> read_step_options(const std::filesystem::path& cmake_file);

void to_json(nlohmann::json& j, const Step& step);
void to_json(nlohmann::json& j, const Section& section);
void to_json(nlohmann::json& j, const Chapter& chapter);

}  // namespace lesson
