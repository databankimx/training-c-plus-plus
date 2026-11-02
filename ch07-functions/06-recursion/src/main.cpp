#include <filesystem>
#include <iostream>
#include <string>

// Prints every entry in a folder. A subfolder is handled by calling this function again on that subfolder.
void listFolder(std::filesystem::path folder, int depth) {
    for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(folder)) {
        std::cout << std::string(depth * 2, ' ') << entry.path().filename().string() << "\n";
        if (entry.is_directory()) {
            listFolder(entry.path(), depth + 1);
        }
    }
}

int main() {
    listFolder("sample", 0);
    return 0;
}

// Try: rename one file inside sample, and run again. Does the listing change?
