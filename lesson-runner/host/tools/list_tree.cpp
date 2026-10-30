// list_tree.cpp: a checkpoint tool. It prints the chapters, sections, steps, and homework the runner would show,
// as JSON, so the discovery can be compared with the Rust runner's before the window is built.
//
// Usage:
//   lesson-list                 uses the repository found from this program's folder
//   lesson-list <repo-folder>   uses the folder you give

#include "commands.hpp"
#include "discovery.hpp"

#include <iostream>

int main(int argc, char** argv) {
    std::filesystem::path root = (argc > 1)
        ? std::filesystem::path(argv[1])
        : lesson::find_repo_root(std::filesystem::path(argv[0]).parent_path());

    nlohmann::json tree = lesson::discover(root);
    // The root goes to stderr, so the JSON on stdout can be redirected to a file and parsed.
    std::cerr << "root: " << root.string() << "\n";
    std::cout << tree.dump(2) << "\n";
    return 0;
}
