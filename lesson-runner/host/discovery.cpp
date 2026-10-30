// discovery.cpp: see discovery.hpp.

#include "discovery.hpp"

#include <algorithm>
#include <cctype>
#include <format>
#include <fstream>
#include <optional>
#include <sstream>
#include <string_view>
#include <utility>

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace lesson {
namespace {

// Extra chapters, such as final-project, sort after the numbered chapters.
constexpr unsigned kExtraChapterNumber = 1000;

// Words that are always written in capitals in titles, whatever the folder name says. Matching ignores case.
// Add an acronym here when a folder name would otherwise show it as a normal word.
constexpr std::string_view kAllCapsWords[] = {
    "api", "c", "cli", "ffi", "html", "http", "io", "json", "oo", "oop", "sql", "ui", "url", "xml",
};

// Words with a fixed spelling that isn't simply all capitals.
const std::pair<std::string_view, std::string_view> kSpecialWords[] = {
    {"cpp", "C++"},
    {"cmake", "CMake"},
    {"raii", "RAII"},
    {"stl", "STL"},
    {"rust", "Rust"},
};

// Hyphenated phrases that keep their hyphen in titles, such as "Re-exporting".
const std::pair<std::string_view, std::string_view> kSpecialPhrases[] = {
    {"re-exporting", "Re-exporting"},
};

// Phrases that appear inside a folder name and become a spaced title, such as "big-o" becoming "Big O". The
// replacement has no hyphen, so the title is split into words as usual. Matching ignores case.
const std::pair<std::string_view, std::string_view> kInlinePhrases[] = {
    {"big-o", "Big O"},
};

std::string lowercase(std::string_view text) {
    std::string result(text);
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return result;
}

std::string uppercase(std::string_view text) {
    std::string result(text);
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
    return result;
}

// The fixed spelling or all-caps form of a word, if it's on one of the lists.
std::optional<std::string> special_word(std::string_view word) {
    const std::string key = lowercase(word);
    for (const auto& [from, to] : kSpecialWords) {
        if (key == from) return std::string(to);
    }
    for (const auto& caps : kAllCapsWords) {
        if (key == caps) return uppercase(word);
    }
    return std::nullopt;
}

// Capitalizes the first letter of a word, and leaves the rest alone.
std::string capitalize(std::string_view word) {
    std::string result(word);
    if (!result.empty()) {
        result[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(result[0])));
    }
    return result;
}

std::vector<std::string> split_words(std::string_view text) {
    std::vector<std::string> words;
    std::string current;
    for (char c : text) {
        if (c == '-') {
            if (!current.empty()) words.push_back(std::exchange(current, {}));
        } else {
            current.push_back(c);
        }
    }
    if (!current.empty()) words.push_back(std::move(current));
    return words;
}

std::string join(const std::vector<std::string>& words, std::string_view separator) {
    std::string result;
    for (std::size_t i = 0; i < words.size(); ++i) {
        if (i > 0) result += separator;
        result += words[i];
    }
    return result;
}

// The chapter number in a folder name such as ch07-packages, or nothing.
std::optional<unsigned> chapter_number(std::string_view name) {
    if (!name.starts_with("ch")) return std::nullopt;
    std::string_view rest = name.substr(2);
    unsigned value = 0;
    std::size_t digits = 0;
    while (digits < rest.size() && std::isdigit(static_cast<unsigned char>(rest[digits]))) {
        value = value * 10 + static_cast<unsigned>(rest[digits] - '0');
        ++digits;
    }
    if (digits == 0) return std::nullopt;
    return value;
}

// Extra chapters are named final-something.
std::optional<unsigned> extra_chapter_number(std::string_view name) {
    if (name.starts_with("final-")) return kExtraChapterNumber;
    return std::nullopt;
}

// A display title such as "Ch07 · Packages", from a folder name such as ch07-packages.
std::string chapter_title(std::string_view name, unsigned number) {
    std::string_view rest = name;
    if (rest.starts_with("ch")) rest.remove_prefix(2);
    while (!rest.empty() && std::isdigit(static_cast<unsigned char>(rest.front()))) rest.remove_prefix(1);
    while (!rest.empty() && rest.front() == '-') rest.remove_prefix(1);

    std::vector<std::string> words;
    for (const std::string& word : split_words(rest)) {
        if (auto special = special_word(word)) {
            words.push_back(*special);
        } else {
            words.push_back(capitalize(word));
        }
    }

    // Extra chapters (number 1000 and above) have no chapter number in their title.
    if (number >= kExtraChapterNumber) return join(words, " ");
    return std::format("Ch{:02} \u00B7 {}", number, join(words, " "));
}

// Replaces each inline phrase that appears as whole words in a name, so its hyphens don't split it apart.
std::string protect_phrases(std::string text) {
    for (const auto& [from, to] : kInlinePhrases) {
        const std::string key(from);
        std::size_t at = 0;
        while (at < text.size()) {
            const std::size_t found = lowercase(text).find(key, at);
            if (found == std::string::npos) break;
            const std::size_t end = found + key.size();
            const bool starts_word = found == 0 || text[found - 1] == '-';
            const bool ends_word = end == text.size() || text[end] == '-';
            if (starts_word && ends_word) {
                text.replace(found, key.size(), to);
                at = found + to.size();
            } else {
                at = found + 1;
            }
        }
    }
    return text;
}

// A step title such as "Hello world", from a folder name such as 02-hello-world. Only the first word is
// capitalized, except for words on the lists, which are capitalized wherever they appear.
std::string step_title(std::string_view name) {
    std::string_view rest = name;
    while (!rest.empty() && std::isdigit(static_cast<unsigned char>(rest.front()))) rest.remove_prefix(1);
    while (!rest.empty() && rest.front() == '-') rest.remove_prefix(1);

    for (const auto& [from, to] : kSpecialPhrases) {
        if (lowercase(rest) == from) return std::string(to);
    }

    std::vector<std::string> words;
    for (const std::string& word : split_words(protect_phrases(std::string(rest)))) {
        if (auto special = special_word(word)) {
            words.push_back(*special);
        } else if (!words.empty()) {
            words.push_back(word);
        } else {
            words.push_back(capitalize(word));
        }
    }
    return join(words, " ");
}

// The number of a sub-chapter folder such as s01-what-is-ownership, or nothing.
std::optional<unsigned> section_number(std::string_view name) {
    if (!name.starts_with('s')) return std::nullopt;
    std::string_view rest = name.substr(1);
    unsigned value = 0;
    std::size_t digits = 0;
    while (digits < rest.size() && std::isdigit(static_cast<unsigned char>(rest[digits]))) {
        value = value * 10 + static_cast<unsigned>(rest[digits] - '0');
        ++digits;
    }
    if (digits == 0) return std::nullopt;
    return value;
}

std::string read_file(const fs::path& file) {
    std::ifstream in(file, std::ios::binary);
    std::ostringstream text;
    text << in.rdbuf();
    return text.str();
}

bool is_source_file(const fs::path& path) {
    const std::string ext = lowercase(path.extension().string());
    return ext == ".cpp" || ext == ".cc" || ext == ".cxx" || ext == ".h" || ext == ".hpp";
}

// Whether a step's sources contain a test, and whether they contain a main function.
// Both are read from the files on disk, under src and tests.
std::pair<bool, bool> scan_sources(const fs::path& step) {
    bool tests = false;
    bool main = false;
    for (const char* folder : {"src", "tests"}) {
        std::error_code ignored;
        const fs::path dir = step / folder;
        if (!fs::is_directory(dir, ignored)) continue;
        for (const auto& entry : fs::recursive_directory_iterator(dir, ignored)) {
            if (!entry.is_regular_file(ignored) || !is_source_file(entry.path())) continue;
            const std::string text = read_file(entry.path());
            tests = tests || text.find("TEST_CASE(") != std::string::npos;
            main = main || text.find("int main(") != std::string::npos;
        }
    }
    return {tests, main};
}

// Whether a step's CMakeLists.txt declares CTest tests. Those are the step's tests, even without TEST_CASE.
bool cmake_declares_tests(const fs::path& step) {
    std::ifstream in(step / "CMakeLists.txt");
    std::ostringstream text;
    text << in.rdbuf();
    return text.str().find("add_test(") != std::string::npos;
}

// The label shown above a chapter's homework. It's "Homework" unless the homework folder has a title.txt, whose first
// line replaces it, such as "Create a Calculator".
std::string homework_title(const fs::path& homework) {
    std::ifstream in(homework / "title.txt");
    std::string line;
    if (in && std::getline(in, line)) {
        while (!line.empty() && std::isspace(static_cast<unsigned char>(line.back()))) line.pop_back();
        if (!line.empty()) return line;
    }
    return "Homework";
}

// The steps in a folder: each sub-folder with a lesson.md or a CMakeLists.txt, except sections and homework.
std::vector<Step> steps_in(const fs::path& folder) {
    std::vector<Step> steps;
    std::error_code ignored;
    if (!fs::is_directory(folder, ignored)) return steps;

    for (const auto& entry : fs::directory_iterator(folder, ignored)) {
        const fs::path path = entry.path();
        if (!entry.is_directory(ignored)) continue;
        if (!fs::is_regular_file(path / "lesson.md", ignored) && !fs::is_regular_file(path / "CMakeLists.txt", ignored)) {
            continue;
        }
        // Sub-chapter folders (sNN-...) are listed as sections, and the homework folder as homework.
        const std::string name = path.filename().string();
        if (section_number(name).has_value() || name == "homework") continue;

        auto [source_tests, has_main] = scan_sources(path);
        const bool has_tests = source_tests || cmake_declares_tests(path);
        Step step;
        step.name = name;
        step.title = step_title(name);
        step.path = path.string();
        step.has_code = fs::is_regular_file(path / "CMakeLists.txt", ignored);
        step.has_tests = has_tests;
        step.has_main = has_main;
        step.has_visualizer = fs::is_regular_file(path / "visualize.html", ignored);
        step.options = read_step_options(path / "CMakeLists.txt");
        steps.push_back(std::move(step));
    }

    std::sort(steps.begin(), steps.end(), [](const Step& a, const Step& b) { return a.name < b.name; });
    return steps;
}

// Sub-chapters are folders named sNN-... inside a chapter. They are shown as "4.1 What is ownership".
std::vector<Section> sections_in(const fs::path& chapter, unsigned chapter_no) {
    std::vector<std::pair<unsigned, Section>> found;
    std::error_code ignored;
    if (!fs::is_directory(chapter, ignored)) return {};

    for (const auto& entry : fs::directory_iterator(chapter, ignored)) {
        const fs::path path = entry.path();
        if (!entry.is_directory(ignored)) continue;
        const std::string name = path.filename().string();
        const auto number = section_number(name);
        if (!number) continue;

        Section section;
        section.name = name;
        section.title = std::format("{}.{} {}", chapter_no, *number, step_title(name.substr(1)));
        section.path = path.string();
        section.steps = steps_in(path);
        found.emplace_back(*number, std::move(section));
    }

    std::sort(found.begin(), found.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
    std::vector<Section> sections;
    for (auto& [number, section] : found) sections.push_back(std::move(section));
    return sections;
}

}  // namespace

std::filesystem::path find_repo_root(const std::filesystem::path& start) {
    std::error_code ignored;
    fs::path folder = fs::absolute(start, ignored);
    while (true) {
        if (fs::is_directory(folder / "lesson-runner", ignored)) return folder;
        if (!folder.has_parent_path() || folder.parent_path() == folder) break;
        folder = folder.parent_path();
    }
    return start;
}

std::vector<Chapter> discover(const fs::path& root) {
    std::vector<std::pair<unsigned, Chapter>> found;
    std::error_code ignored;
    if (!fs::is_directory(root, ignored)) return {};

    for (const auto& entry : fs::directory_iterator(root, ignored)) {
        const fs::path path = entry.path();
        if (!entry.is_directory(ignored)) continue;
        const std::string name = path.filename().string();
        const auto number = chapter_number(name).or_else([&] { return extra_chapter_number(name); });
        if (!number) continue;

        Chapter chapter;
        chapter.name = name;
        chapter.title = chapter_title(name, *number);
        chapter.path = path.string();
        chapter.steps = steps_in(path);
        chapter.homework = steps_in(path / "homework");
        chapter.homework_path = (path / "homework").string();
        chapter.homework_title = homework_title(path / "homework");
        chapter.sections = sections_in(path, *number);
        found.emplace_back(*number, std::move(chapter));
    }

    std::sort(found.begin(), found.end(), [](const auto& a, const auto& b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second.name < b.second.name;
    });
    std::vector<Chapter> chapters;
    for (auto& [number, chapter] : found) chapters.push_back(std::move(chapter));
    return chapters;
}

nlohmann::json list_parts(const fs::path& root) {
    const std::vector<Chapter> chapters = discover(root);
    std::vector<bool> used(chapters.size(), false);

    // parts.json is optional. Without it, or if it can't be read, every chapter ends up under "Other".
    json config = json::object();
    std::ifstream in(root / "parts.json");
    if (in) {
        try {
            config = json::parse(in);
        } catch (const json::exception&) {
            config = json::object();
        }
    }

    auto findChapter = [&chapters](const std::string& name) -> int {
        for (std::size_t i = 0; i < chapters.size(); ++i) {
            if (chapters[i].name == name) return static_cast<int>(i);
        }
        return -1;
    };

    json parts = json::array();
    if (config.contains("parts") && config.at("parts").is_array()) {
        for (const json& part : config.at("parts")) {
            json group{{"title", part.value("title", "")}, {"chapters", json::array()}};
            for (const json& nameValue : part.value("chapters", json::array())) {
                const int index = findChapter(nameValue.get<std::string>());
                if (index < 0 || used[static_cast<std::size_t>(index)]) continue;
                used[static_cast<std::size_t>(index)] = true;
                group["chapters"].push_back(json(chapters[static_cast<std::size_t>(index)]));
            }
            if (!group["chapters"].empty()) parts.push_back(group);
        }
    }

    json other = json::array();
    for (std::size_t i = 0; i < chapters.size(); ++i) {
        if (!used[i]) other.push_back(json(chapters[i]));
    }
    if (!other.empty()) {
        parts.push_back(json{{"title", "Other"}, {"chapters", other}});
    }
    return parts;
}

std::vector<StepOption> read_step_options(const fs::path& cmake_file) {
    std::vector<StepOption> options;
    std::ifstream in(cmake_file);
    std::string line;
    while (std::getline(in, line)) {
        const std::size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos) continue;
        const std::string text = line.substr(start);
        if (text.rfind("option(", 0) != 0) continue;

        // option(NAME "description" ON), where NAME ends at the first space, tab, or quote.
        const std::size_t nameEnd = text.find_first_of(" \t\"", 7);
        if (nameEnd == std::string::npos) continue;
        const std::string name = text.substr(7, nameEnd - 7);
        if (name.empty()) continue;

        const std::size_t quoteOpen = text.find('"', nameEnd);
        if (quoteOpen == std::string::npos) continue;
        const std::size_t quoteClose = text.find('"', quoteOpen + 1);
        if (quoteClose == std::string::npos) continue;
        const std::string description = text.substr(quoteOpen + 1, quoteClose - quoteOpen - 1);

        const std::size_t close = text.find(')', quoteClose);
        std::string value = text.substr(quoteClose + 1,
                                        close == std::string::npos ? std::string::npos : close - quoteClose - 1);
        const std::size_t first = value.find_first_not_of(" \t");
        const std::size_t last = value.find_last_not_of(" \t");
        value = first == std::string::npos ? std::string() : value.substr(first, last - first + 1);

        options.push_back(StepOption{name, description, value == "ON"});
    }
    return options;
}

std::filesystem::path work_root(const fs::path& repo_root) {
    return repo_root / ".lesson-runner" / "work";
}

void to_json(nlohmann::json& j, const Step& step) {
    j = {
        {"name", step.name},
        {"title", step.title},
        {"path", step.path},
        {"has_code", step.has_code},
        {"has_tests", step.has_tests},
        {"has_main", step.has_main},
        {"has_visualizer", step.has_visualizer},
    };
    j["options"] = json::array();
    for (const StepOption& option : step.options) {
        j["options"].push_back(json{{"name", option.name}, {"description", option.description}, {"default", option.default_on}});
    }
}

void to_json(nlohmann::json& j, const Section& section) {
    j = {
        {"name", section.name},
        {"title", section.title},
        {"path", section.path},
        {"steps", section.steps},
    };
}

void to_json(nlohmann::json& j, const Chapter& chapter) {
    j = {
        {"name", chapter.name},
        {"title", chapter.title},
        {"path", chapter.path},
        {"steps", chapter.steps},
        {"homework", chapter.homework},
        {"homework_path", chapter.homework_path},
        {"homework_title", chapter.homework_title},
        {"sections", chapter.sections},
    };
}

}  // namespace lesson
