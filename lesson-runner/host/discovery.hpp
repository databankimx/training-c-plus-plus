// discovery.hpp: finds the chapters, sections, steps, and homework in the training repository.
// The rules match the Rust runner's discovery.rs, with two differences for C++: a step has a CMakeLists.txt rather
// than a Cargo.toml, and tests are found by TEST_CASE rather than #[test].

#pragma once

#include <json.hpp>

#include <filesystem>
#include <string>
#include <vector>

namespace lesson {

struct Step {
    std::string name;
    std::string title;
    std::string path;
    bool has_code = false;
    bool has_tests = false;
    bool has_main = false;
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
    std::vector<Section> sections;
};

// Walks up from a starting folder (normally the program's own folder) until it finds the folder that holds
// lesson-runner. That folder is the training repository's root.
std::filesystem::path find_repo_root(const std::filesystem::path& start);

// Every chapter folder in the repository, in chapter order.
std::vector<Chapter> discover(const std::filesystem::path& root);

void to_json(nlohmann::json& j, const Step& step);
void to_json(nlohmann::json& j, const Section& section);
void to_json(nlohmann::json& j, const Chapter& chapter);

}  // namespace lesson
